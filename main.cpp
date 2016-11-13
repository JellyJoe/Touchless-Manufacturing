#include <stdio.h>
#include <tchar.h>
#include "Serial.h"	// Library described above
#include <string>
#include <iostream>
#include <unistd.h>
using namespace std;
// application reads from the specified serial port and reports the collected data
int _tmain(int argc, _TCHAR* argv[])
{
    printf("Welcome to the UARM Terminal app!\n\n");

    Serial* ArmSp = new Serial("COM3");    // adjust as needed

    if (ArmSp->IsConnected())
        cout << "The Arm is Connected." << endl;

    char outgoingData[256] = "";
    char incomingData[256] = "";
    char command[256];
    int dataLength = 255;
    while(ArmSp->IsConnected())
    {
        cout << "Menu" << endl;
        cout << "1.Demo Mode" << endl;
        cout << "2.Learning Mode" << endl;
        cout << "3.Auto Detection Mode" << endl;
        cout <<"Enter Command:";
        cin >> command;
        if(strcmp(command,"1")==0)
        {
            strcpy(outgoingData,"a");
            ArmSp->WriteData(outgoingData,dataLength);
            Sleep(1000);
            strcpy(outgoingData,command);
            ArmSp->WriteData(outgoingData,dataLength);
        }
        else if(strcmp(command,"2") == 0)
        {
            strcpy(outgoingData,command);
            ArmSp->WriteData(outgoingData,dataLength);
            ArmSp->ReadData(incomingData,dataLength);
            char data[256]="";
            char position[1];
            do
            {
                cout << "S.Manual Calibration with pump" << endl;
                cout << "O.Without Pump" << endl;
                cout << "D.Done" << endl;
                cin >> position[0];
                strcpy(outgoingData,position);
                ArmSp->WriteData(outgoingData,dataLength);
                cout << position << endl;
                Sleep(1000);
                //ArmSp->ReadData(data,dataLength);
                //cout << data << endl;

            }
            while(position[0] != 'd');

        }

        else if(strcmp(command,"3") == 0)
        {
            char position[1];
            /*strcpy(outgoingData,command);
            ArmSp->WriteData(outgoingData,dataLength);
            ArmSp->ReadData(incomingData,dataLength);
            do
            {
                cout << "B.Set Stamper Position" << endl;
                cout << "O.Without Pump" << endl;
                cout << "D.Done" << endl;
                cin >> position[0];
                strcpy(outgoingData,position);
                ArmSp->WriteData(outgoingData,dataLength);
                cout << position << endl;
                Sleep(1000);
                ArmSp->ReadData(data,dataLength);
                cout << data << endl;

            }
            while(position[0] != 'd');*/
            int result;
            result = ArmSp->ReadData(incomingData, dataLength);
            incomingData[result] = '\0';
            cout << "X:";
            Sleep(500);
            cout << incomingData << endl;

        }

    }


    // printf("Bytes read:

    Sleep(500);
    return 0;
}
