#include "Arm.h"
#include "MyClass.h"
#include "Serial.h"
#include <iostream>
#include <QProcess>
#include <QDir>
#include <QDebug>

Arm::Arm(QObject *parent) :
    QObject(parent)
{
    ArmSp = new Serial((char*)"COM6");    // adjust as needed

    if (ArmSp->IsConnected())
    {
        qDebug() << "Arm is connected";
    }
    else
    {

        qDebug() << "Arm couldn't connect";

    }

    outgoingData[256] = {'\0'};
    dataLength = 256;

}


void Arm::demoClicked()
{

    strcpy(outgoingData,"a");
    ArmSp->WriteData(outgoingData,dataLength);
    Sleep(500);
    strcpy(outgoingData,"1");
    ArmSp->WriteData(outgoingData,dataLength);
    Sleep(1000);

}

void Arm::manualLaunched()
{
    strcpy(outgoingData,"2");
    ArmSp->WriteData(outgoingData,dataLength);
}

void Arm::saveWithPump()
{
    strcpy(outgoingData,"s");
    ArmSp->WriteData(outgoingData,dataLength);
}

void Arm::saveWithoutPump()
{
    strcpy(outgoingData,"o");
    ArmSp->WriteData(outgoingData,dataLength);
}

void Arm::executeManualMovement()
{
    strcpy(outgoingData,"d");
    ArmSp->WriteData(outgoingData,dataLength);

}

void Arm::stopMovement()
{

    delete ArmSp;
    ArmSp = new Serial((char*)"COM6");
}

