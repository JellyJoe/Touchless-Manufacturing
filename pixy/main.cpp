/*PrimeDev - 2016*/
#include <stdio.h>
#include <tchar.h>
#include "header.h"  // Library described above
#include <string>
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
    char incomingData[2] = "";//to pre-allocate memory
    int dataLength = 255;
    int result = 0;

    //if program is connected to the serial display a successful message
    if(SP->isConnected())
        cout << "Pixy is Connected...\n";
    //loop if is connected
    while (SP->isConnected())
    {
        //read incoming data from arduino
        result  = SP->readData(incomingData, dataLength);
        if(result != 0)
        {
            cout << incomingData << endl;
            for(int i = 0; i< sizeof(incomingData); i++)
            {
                incomingData[i] = '\0';
            }
        }
        Sleep(500);
    }



    return 0;
}






