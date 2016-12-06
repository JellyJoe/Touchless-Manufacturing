//Header file
#include "Arm.h"
#include "MyClass.h"
#include "Pixy.h"
#include "Serial.h"
#include <iostream>
#include <QProcess>
#include <QDir>
#include <QDebug>

using namespace std;

Pixy::Pixy(QObject * parent) :
    QObject(parent)
{
    //Pixy Serial Port Number
    pixySP = new Serial ((char*)"COM5");
    if(pixySP->IsConnected())
    {
        qDebug() << "Pixy is connected";
    }
    else
    {
        qDebug() << "Pixy couldn't connect";
    }
    incomingData[MAX_DATA_LENGTH] = {'\0'};
    outgoingData[MAX_DATA_LENGTH] = {'\0'};
    //PixyMon path
    path = "C:\\PixyMon\\bin\\PixyMon.exe";
    check = 0;
}

//Execute pixy
void Pixy::getBlocks()
{
    strcpy(outgoingData, "y");
    pixySP->WriteData(outgoingData, MAX_DATA_LENGTH);

}

//Retrieve value from pixy and check if value receive is "T" means blocks detected and return true
//else return false
bool Pixy::checkBlocks()
{
    int result = 0;
    bool validate = true;

    result  = pixySP->ReadData(incomingData, MAX_DATA_LENGTH);
    incomingData[result] = '\0';

    if(incomingData[0] == 'F')
    {
        validate = false;
    }
    else if(incomingData[0] == 'T')
    {
        validate = true;
    }

    Sleep(500);

    return validate;
}

//Execute Pixymon for signature setting
void Pixy::executePixymon()
{
    qDebug() << "PixyMon run";
    QProcess::execute(path);

}

//Stop the pixy
void Pixy::stopPixy()
{
    //Deleting the Serial Connection
    delete pixySP;
    //Restarting the connection for the Arm
    pixySP = new Serial((char*)"COM5");
}


