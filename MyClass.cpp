#include "MyClass.h"
#include "Serial.h"
#include <iostream>
#include <QProcess>
#include <QDir>


MyClass::MyClass(QObject *parent) :
    QObject(parent)
{
    SP = new Serial("COM6");    // adjust as needed

    if (SP->IsConnected())
    {
        std::cout << "Pixy is connected" << endl;
    }
    else
    {

        std::cout << "Pixy couldn't connect" << endl;

    }

}


void MyClass::demoClicked()
{


    char outgoingData[256] = "";
    //char incomingData[256] = "";
    int dataLength = 255;

    strcpy(outgoingData,"1");
    SP->WriteData(outgoingData,dataLength);
    Sleep(1000);

}

void MyClass::pixyRun()
{

    qDebug() << "PixyMon run";
    //QString program = "C:\\Program Files (x86)\PixyMon\bin\PixyMon.exe";

    //QProcess *myProcess = new QProcess();
    //myProcess->start(program);
    //myProcess->start("C:\\PixyMon.exe");
    QProcess::execute("C:\\PixyMon\\bin\\PixyMon.exe");
}


