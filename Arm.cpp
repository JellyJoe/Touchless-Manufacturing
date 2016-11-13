#include "Arm.h"
#include "MyClass.h"
#include "Serial.h"
#include <iostream>
#include <QProcess>
#include <QDir>

Arm::Arm(QObject *parent) :
    QObject(parent)
{
    ArmSp = new Serial((char*)"COM6");    // adjust as needed

    if (ArmSp->IsConnected())
    {
        std::cout << "Arm is connected" << endl;
    }
    else
    {

        std::cout << "Arm couldn't connect" << endl;

    }

    outgoingData[256] = ' ';
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

void Arm::manualLuanched()
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
    //exit data send
    //strcpy(outgoingData,"e");
    //ArmSp->WriteData(outgoingData,dataLength);

    delete ArmSp;
    ArmSp = new Serial((char*)"COM6");
}

