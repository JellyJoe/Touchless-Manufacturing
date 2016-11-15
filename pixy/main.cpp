/*PrimeDev - 2016*/
#include <stdio.h>
#include <tchar.h>
#include "header.h"  // Library described above
#include <string>
#include <iostream>
using namespace std;

// application reads from the specified serial port and reports the collected data
int main()
{

    printf("Welcome to the serial test app!\n\n");
    //serial port number
    Serial* SP = new Serial("\\\\.\\COM4");    // adjust as needed
    //buffer
    char incomingData[256] = "", writeX[256] = "", writeY[4]="", writeZ[4]="", stuff[256]="", XYZData[12];// don't forget to pre-allocate memory
    string x, y, z, concatXYZ;
    char * getValue;
    string start, modify;
    bool complete = false;
    int dataLength = 255;
    int result = 0;
    int counter = 0;
    if(SP->isConnected())
        cout << "Connected...\n";

    while (SP->isConnected())
    {
        cout << "Start reading coordinates? (Y/N): ";
        getline(cin, start);

        if(start == "Y")
        {
            char *v = new char[start.size()+1];
            copy(start.begin(), start.end(), v);
            v[start.size()] = '\n';
            SP->writeData(v, dataLength);
            delete [] v;
            Sleep(500);
            SP->readData(incomingData, dataLength);//read data in serial
            getValue = strtok(incomingData, " ");//seperate the buffer's values
            while(getValue != NULL)
            {
                if(counter == 0)//1st seperated value
                {
                    x = getValue;
                    counter++;//increment counter
                    cout << "x:" << x << "\t";

                }
                else if(counter == 1)//2nd seperated value
                {
                    y = getValue;

                    counter++;//increment counter
                    cout << "y:" << y << "\t";

                }
                else if(counter == 2)//3rd seperated value
                {
                    z = getValue;
                    cout << "z:" << z << endl;
                    counter = 0;//reset counter
                }
                getValue  = strtok(NULL, " ");
                Sleep(500);//sleep 0.5 sec

            }
            if(x!="" && y != "" && z!= "")
            {

                concatXYZ = x + " " + y + " " + z;
                cout << "Verifying...\n";
                char *c_string = new char[concatXYZ.size()+1];
                copy(concatXYZ.begin(), concatXYZ.end(), c_string);
                c_string[concatXYZ.size()] = '\n';
                SP->writeData(c_string, dataLength);
                SP->readData(stuff, dataLength);
                puts(stuff);
                delete [] c_string;
            }


        }
        else if(start == "N")
            break;

    }



    return 0;
}





