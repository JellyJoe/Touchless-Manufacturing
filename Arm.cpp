//Header file
#include "Arm.h"
#include "MyClass.h"
#include "Serial.h"
#include <iostream>
#include <QProcess>
#include <QDir>
#include <QDebug>


//Arm Class
Arm::Arm(QObject *parent) : QObject(parent)
{   
    //Arm connecting to serial port
    ArmSp = new Serial((char*)"COM6");    // adjust as needed

    //If arm is connected prompt message in debug console
    if (ArmSp->IsConnected())
    {
        qDebug() << "Arm is connected";
    }
    else
    {
        qDebug() << "Arm couldn't connect";
    }

    //Initializing variables
    outgoingData[MAX_OUTGOING_DATA_LENGTH] = {'\0'};
    incomingData[MAX_OUTGOING_DATA_LENGTH] = {'\0'};
    cycle = 0;

}

//Demo Button Function
void Arm::demoClicked()
{
    //Sending Signal A to attach the servo
    strcpy(outgoingData,"a");
    ArmSp->WriteData(outgoingData, MAX_OUTGOING_DATA_LENGTH);
    Sleep(500);

    //Sending Signal 1 to start the demo mode
    strcpy(outgoingData,"1");
    ArmSp->WriteData(outgoingData, MAX_OUTGOING_DATA_LENGTH);
    Sleep(1000);
}

//Manual Launched Function
void Arm::manualLaunched()
{
    //Sending Signal 2 to start the Manual Configuration
    strcpy(outgoingData,"2");
    ArmSp->WriteData(outgoingData, MAX_OUTGOING_DATA_LENGTH);
}

//Saving the Coordinates with Pump Enable
void Arm::saveWithPump()
{
    //Sending Signal S to save the coordinates
    strcpy(outgoingData,"s");
    ArmSp->WriteData(outgoingData, MAX_OUTGOING_DATA_LENGTH);
}

//Saving the Coordinates with Pump Enable
void Arm::saveWithoutPump()
{
    //Sending Signal O to save the coordinates
    strcpy(outgoingData,"o");
    ArmSp->WriteData(outgoingData, MAX_OUTGOING_DATA_LENGTH);
}

//Executing Manual Movement
void Arm::executeManualMovement()
{
    //Sending Signal D to execute the manual movement for the arm
    strcpy(outgoingData,"d");
    ArmSp->WriteData(outgoingData, MAX_OUTGOING_DATA_LENGTH);

}

//Saving Position A
void Arm::setPositionA()
{
    strcpy(outgoingData,"A");
    ArmSp->WriteData(outgoingData,MAX_OUTGOING_DATA_LENGTH);
}

//Saving Position B
void Arm::setPositionB()
{
    strcpy(outgoingData,"b");
    ArmSp->WriteData(outgoingData,MAX_OUTGOING_DATA_LENGTH);
}

//Saving Position C
void Arm::setPositionC()
{
    strcpy(outgoingData,"c");
    ArmSp->WriteData(outgoingData,MAX_OUTGOING_DATA_LENGTH);
}

//Saving Height of the Object
void Arm::setHeight()
{
    strcpy(outgoingData,"h");
    ArmSp->WriteData(outgoingData,MAX_OUTGOING_DATA_LENGTH);
}

//Execute Auto Arm Movement
void Arm::executeAutoMovement()
{
    strcpy(outgoingData,"e");
    ArmSp->WriteData(outgoingData,MAX_OUTGOING_DATA_LENGTH);
    do
    {
        int result=0;
        result = ArmSp->ReadData(incomingData, MAX_OUTGOING_DATA_LENGTH);
        incomingData[result] = '\0';
    }
    while(incomingData[0]!='D');
    cycle++;
}

//Stop the Arm from moving
void Arm::stopMovement()
{
    //Deleting the Serial Connection
    delete ArmSp;
    //Restarting the connection for the Arm
    ArmSp = new Serial((char*)"COM6");
}
