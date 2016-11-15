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
    string sig, sigValue, width, widthValue, x, xValue, y, yValue, z, zValue, concatXYZ;
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
            Sleep(1000);
            SP->readData(incomingData, dataLength);//read data in serial
            if(incomingData[0] != 'E')
            {
                getValue = strtok(incomingData, " ");//seperate the buffer's value

                while(getValue != NULL)
                {
                    if(counter == 0)//1st seperated value
                    {
                        sig = getValue;
                        counter++;//increment counter

                    }
                    else if(counter == 1)//2nd seperated value
                    {
                        sigValue = getValue;

                        counter++;//increment counter

                    }
                    else if(counter == 2)//3rd seperated value
                    {
                        x = getValue;
                        counter++;//reset counter
                    }
                    else if(counter == 3)
                    {
                        xValue = getValue;
                        counter++;

                    }
                    else if(counter == 4)
                    {
                        y = getValue;
                        counter ++;
                    }
                    else if(counter == 5)
                    {
                        yValue = getValue;
                        counter ++;
                    }
                    else if(counter == 6)
                    {
                        width = getValue;
                        counter ++;
                    }
                    else if(counter == 7)
                    {
                        widthValue = getValue;
                        counter ++;
                    }
                    else if(counter == 8)
                    {
                        z = getValue;
                        counter ++;
                    }
                    else if(counter == 9)
                    {
                        zValue = getValue;
                        counter=0;
                    }
                    getValue  = strtok(NULL, " ");
                    Sleep(100);//sleep 0.5 sec

                }
                cout << "x: " << xValue << " y: " << yValue << " z: " << zValue;
            }
            else
                cout << incomingData << endl;
            /* if(x!="" && y != "" && z!= "")
             {

                 concatXYZ = x + " " + y + " " + z;
                 cout << "Verifying...\n";
                 char data[256]="";

                 do
                 {

                     cout << "Enter x y z: ";
                    getline(cin, modify);
                     char * a = new char[modify.size()+1];
                     copy(modify.begin(), modify.end(), a)  ;
                     a[modify.size()] = '\n';
                     SP->writeData(a, dataLength);
                     Sleep(1000);
                     SP->readData(data, dataLength);
                     cout << data << endl;
                     delete [] a;

                 }
                 while(modify!="0");

             }*/


        }
        else if(start == "N")
            break;

    }



    return 0;
}





