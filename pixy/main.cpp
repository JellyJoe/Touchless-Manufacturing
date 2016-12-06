//header file
#include <stdio.h>
#include <tchar.h>
#include "header.h"  // Library described above
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;

// application reads from the specified serial port and reports the collected data
int _tmain(int argc, _TCHAR* argv[])
{
    printf("Welcome to the Pixy Terminal app!\n\n");
    Sleep(1000);
    //serial port number
    Serial* SP = new Serial("\\\\.\\COM4");    // adjust as needed
    //variables
    char incomingData[256]="", outgoingData[256]="", start[1];//to pre-allocate memory
    int dataLength =256;
    int result = 0;

    //if program is connected to the serial display a successful message
    if(SP->isConnected())
    {
        cout << "Pixy is Connected...\n";
        cout << "Enter a value: ";
        cin >> start;
        if(strcmp(start, "y") == 0)
        {
            strcpy(outgoingData, start);
            SP->writeData(outgoingData, dataLength);
            //loop if is connected
            while(strcmp(outgoingData, "y") == 0)
            {
                //read incoming data from arduino
                result  = SP->readData(incomingData, dataLength);

                if(result != 0)
                {
                    //check if arduino is printing data
                    //if data is "T" means signature is found
                    if(strcmp(incomingData, "T") == 0)
                    {
                        cout << incomingData << endl;
                    }
                    else
                    {
                        cout << incomingData << endl;
                    }
                }

            }
        }
    }
    return 0;
}





