/*#include <stdio.h>
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

	Serial* SP = new Serial("COM3");    // adjust as needed

	if (SP->IsConnected())
		printf("We're connected");

	char outgoingData[256] = "";
	char incomingData[256] = "";
    int dataLength = 255;
	char command[256];

	int readResult = 0;
	while(SP->IsConnected())
	{
        cout <<"Enter Command:";
        cin >> command;
        if(strcmp(command,"1")==0)
        {
            strcpy(outgoingData,command);
            SP->WriteData(outgoingData,dataLength);
        }
        else if(strcmp(command,"2") == 0)
        {
            strcpy(outgoingData,command);
            SP->WriteData(outgoingData,dataLength);

            char position[2],pump_status[2];
            do
            {
                cout << "S.Manual Calibration with pump" << endl;
                cout << "O.Without Pump" << endl;
                cout << "D.Done" << endl;
                cin >> position;
                strcpy(outgoingData,position);
                SP->WriteData(outgoingData,dataLength);
                Sleep(1000);
            }while((strcmp(position,"d")!=0));

            cout << "The arm is running." << endl;
            cout << "Enter C to stop the arm." << endl;
            cin >> command;
            strcpy(outgoingData,command);
            SP->WriteData(outgoingData,dataLength);


        }

        else if(strcmp(command,"3")== 0)
        {
            strcpy(outgoingData,command);
            SP->WriteData(outgoingData,dataLength);
            char setting;
            cout << "Auto Detect" << endl;
            cout << "Set position b" << endl;
            cin >> setting;
            SP->WriteData(outgoingData,dataLength);
            cout << "Set position c" << endl;
            cin >> setting;
            SP->WriteData(outgoingData,dataLength);








        }

		// printf("Bytes read: (0 means no data available) %i\n",readResult);

		Sleep(500);
	}

	return 0;
}

*/
