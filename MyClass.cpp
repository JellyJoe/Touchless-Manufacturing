#include "MyClass.h"
#include "Serial.h"
#include <iostream>

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


    strcpy(outgoingData,"a");
    SP->WriteData(outgoingData,dataLength);
    Sleep(1000);
    strcpy(outgoingData,"1");
    SP->WriteData(outgoingData,dataLength);
    Sleep(1000);
    strcpy(outgoingData,"d");
    SP->WriteData(outgoingData,dataLength);

}


