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
    printf("Welcome to the serial test app!\n\n");

    Serial* ArmSp = new Serial("COM3");    // adjust as needed

    if (ArmSp->IsConnected())
        printf("We're connected to arm");

    char outgoingData[256] = "";
    char incomingData[256] = "";
    char command[256];
    int dataLength = 255;
    int readResult = 0;
    while(ArmSp->IsConnected())
    {
        cout <<"Enter Command:";
        cin >> command;
        if(strcmp(command,"1")==0)
        {
            strcpy(outgoingData,command);
            ArmSp->WriteData(outgoingData,dataLength);
        }
        else if(strcmp(command,"2") == 0)
        {
            strcpy(outgoingData,command);
            ArmSp->WriteData(outgoingData,dataLength);

            char position[2],pump_status[2];
            do
            {
                cout << "S.Manual Calibration with pump" << endl;
                cout << "O.Without Pump" << endl;
                cout << "D.Done" << endl;
                cin >> position;
                strcpy(outgoingData,position);
                ArmSp->WriteData(outgoingData,dataLength);
                Sleep(1000);
            }
            while((strcmp(position,"d")!=0));

            cout << "The arm is running." << endl;
            cout << "Enter C to stop the arm." << endl;
            cin >> command;
            strcpy(outgoingData,command);
            ArmSp->WriteData(outgoingData,dataLength);


        }

        else if(strcmp(command,"5")== 0)
        {
            strcpy(outgoingData,command);
            ArmSp->WriteData(outgoingData,dataLength);
            char setting;
            cout << "Auto Detect" << endl;
            cout << "Set position b" << endl;
            cin >> setting;
            ArmSp->WriteData(outgoingData,dataLength);
            cout << "Set position c" << endl;
            cin >> setting;
            ArmSp->WriteData(outgoingData,dataLength);

            Serial* PixySp = new Serial("COM4");
            if(PixySp->IsConnected())
                cout << "We are connected pixy" << endl;

            result = SP->ReadData(serial_buffer, BUFFER_SIZE - 1);
            serial_buffer[result] = '\0';

            if(serial_buffer != NULL)
            {
                getValue = strtok(serial_buffer, " ");
                while(getValue != NULL)
                {
                    if(counter == 0)
                    {
                        x = getValue;
                        counter++;
                        cout << "x: " << x << "\t\t";
                        Sleep(500);

                    }
                    else if(counter == 1)
                    {
                        y = getValue;
                        counter++;
                        cout << "y: " << y << "\t\t";
                        Sleep(500);
                    }
                    else if(counter == 2)
                    {
                        z = getValue;
                        cout << "z: " << z << "\t\t" << endl;
                        counter = 0;
                        Sleep(500);
                    }
                    getValue = strtok(NULL, " ");
                }
            }




        }


        // printf("Bytes read: (0 means no data available) %i\n",readResult);

        Sleep(500);
    }
    return 0;
}
