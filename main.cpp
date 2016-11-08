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
    int readResult = 0;
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
            strcpy(outgoingData,command);
            ArmSp->WriteData(outgoingData,dataLength);
        }
        else if(strcmp(command,"2") == 0)
        {
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

        else if(strcmp(command,"3")== 0)
        {
            char setting;
            int set_b = 0,set_c = 0;
            cout << "Auto Detect" << endl;
            cout << "B.Set position b" << endl;
            cout << "C.Set position c" << endl;
            cin >> setting;
            while(set_b == 1 && set_c == 1)
            {
                if(strcmp(setting,"b") == 0)
                {
                    set_b = 1;
                    ArmSp->WriteData(outgoingData,dataLength);
                    if(set_c != 1)
                    {
                        cout << "Please Set position C. \n
                         "Press c to Set position C. \n";
                         cin >> setting;
                    }

                }
                if(strcmp(setting,"c") == 0)
                {
                    set_c = 1;
                    ArmSp->WriteData(outgoingData,dataLength);
                    if(set_b != 1)
                    {
                        cout << "Please Set position B. \n
                         "Press c to Set position B. \n";
                         cin >> setting;
                    }

                }
            }
        }


    }


    // printf("Bytes read:
    (0 means no data available) %i\n",readResult);

    Sleep(500);
}
    return 0;
}
