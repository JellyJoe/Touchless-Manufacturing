/*PrimeDev - 2016*/
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
    //serial port number
    Serial* SP = new Serial("\\\\.\\COM4");    // adjust as needed
    //variables
    char incomingData[256] = "", outgoingData[256] = "", start[256]="";//to pre-allocate memory
    string sig, sigValue, width, widthValue, x, xValue, y, yValue, z, zValue, concatXYZ;
    char * getValue;
    int dataLength = 255;
    int result = 0, xData, yData, zData;
    int counter = 0;

    //if program is connected to the serial display a successful message
    if(SP->isConnected())
        cout << "Pixy is Connected...\n";
    //loop if is connected
    while (SP->isConnected())
    {
        //Ask user whether he/she would want to get coordinates.
        //if input Y means yes, program will start receive coordinates from arduino
        //if input N means no, program will stop and terminate
        cout << "Start getting coordinates? (Y/N): ";
        cin >> start;

        if(strcmp(start,"Y")==0)//check if input is Y
        {
            //send char pointer to arduino
            strcpy(outgoingData, start);
            SP->writeData(outgoingData, dataLength);
            //read incoming data from arduino
            //incoming data is in the form of "sig: value x: value y: value width: value height: value"
            //height is z
            //this incoming data uses the pixy print command which prints the whole pixy information in a string
            result  = SP->readData(incomingData, dataLength);
            if(result != 0)
            {
                //Seperate incoming data when the delimeter is a space
                getValue = strtok(incomingData, " ");
                //loop if the seperated incoming data is not null
                while(getValue != NULL)
                {
                    //get signature display
                    if(counter == 0)//1st seperated value
                    {
                        sig = getValue;
                        counter++;//increment counter

                    }
                    //get signature value
                    else if(counter == 1)//2nd seperated value
                    {
                        sigValue = getValue;

                        counter++;//increment counter

                    }
                    //get x display
                    else if(counter == 2)//3rd seperated value
                    {
                        x = getValue;
                        counter++;//increment counter
                    }
                    //get x value
                    else if(counter == 3)//4th seperated value
                    {
                        xValue = getValue;
                        counter++;//increment counter

                    }
                    //get y display
                    else if(counter == 4)//5th seperated value
                    {
                        y = getValue;
                        counter ++;//increment counter
                    }
                    //get y value
                    else if(counter == 5)//6th seperated value
                    {
                        yValue = getValue;
                        counter ++;//increment counter
                    }
                    //get width display
                    else if(counter == 6)//7th seperated value
                    {
                        width = getValue;
                        counter ++;//increment counter
                    }
                    //get width value
                    else if(counter == 7)//8th seperated value
                    {
                        widthValue = getValue;
                        counter ++;//increment counter
                    }
                    //get z display
                    else if(counter == 8)//9th seperated value
                    {
                        z = getValue;
                        counter ++;//increment counter
                    }
                    //get z value
                    else if(counter == 9)//10th seperated value
                    {
                        zValue = getValue;
                        counter=0;//reset counter to 0
                    }
                    getValue  = strtok(NULL, " ");
                    Sleep(100);//sleep 0.1 sec

                }
                //convert the string to integer for comparison purpose
                xData = atoi(xValue.c_str());
                yData = atoi(yValue.c_str());
                zData = atoi(zValue.c_str());
                //if pixy gives out coordinates that is not within the below range set, program will display an error message
                //if within then program will display x, y and z value
                if(xData > 10 && yData > 10 && zData > 10)
                {
                    cout << "x: " << xValue << " y: " << yValue << " z: " << zValue;
                }
                else
                    cout << "No object detected!" << endl;//error message of no object detected!
            }


        }
        else if(strcmp(start, "N") == 0)//terminate program
            break;

    }



    return 0;
}





