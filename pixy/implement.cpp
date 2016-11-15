/*PrimeDev - 2016*/
#include "header.h"
#include <string>
#include <iostream>
using namespace std;
//Function to connect the serial port
Serial::Serial(char *portName)
{
    //We're not yet connected
    this->connected = false;

    //Try to connect to the given port throuh CreateFile
    this->hSerial = CreateFile(portName,
                               GENERIC_READ | GENERIC_WRITE,
                               0,
                               NULL,
                               OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL,
                               NULL);

    //Check if the connection was successfull
    if (this->hSerial == INVALID_HANDLE_VALUE)
    {
        //If not success full display an Error
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
        {

            //Print Error if neccessary
            printf("ERROR: Handle was not attached. Reason: %s not available.\n", portName);

        }
        else
        {
            printf("ERROR!!!");
        }
    }
    else
    {
        //If connected we try to set the comm parameters
        DCB dcbSerialParams = { 0 };

        //Try to get the current
        if (!GetCommState(this->hSerial, &dcbSerialParams))
        {
            //If impossible, show an error
            printf("failed to get current serial parameters!");
        }
        else
        {
            //Define serial connection parameters for the arduino board
            dcbSerialParams.BaudRate = CBR_9600;
            dcbSerialParams.ByteSize = 8;
            dcbSerialParams.StopBits = ONESTOPBIT;
            dcbSerialParams.Parity = NOPARITY;
            //Setting the DTR to Control_Enable ensures that the Arduino is properly
            //reset upon establishing a connection
            dcbSerialParams.fDtrControl = DTR_CONTROL_ENABLE;

            //Set the parameters and check for their proper application
            if (!SetCommState(hSerial, &dcbSerialParams))
            {
                printf("ALERT: Could not set Serial Port parameters");
            }
            else
            {
                //If everything went fine we're connected
                this->connected = true;
                //Flush any remaining characters in the buffers
                PurgeComm(this->hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
                //We wait 2s as the arduino board will be reseting
                Sleep(ARDUINO_WAIT_TIME);
            }
        }
    }

}

Serial::~Serial()
{
    //Check if we are connected before trying to disconnect
    if (this->connected)
    {
        //We're no longer connected
        this->connected = false;
        //Close the serial handler
        CloseHandle(this->hSerial);
    }
}
//Function to read data that is store in the arduino
//If data is readable in the arduino it will return a true result or result equal to 1
//means that there is data read
int Serial::readData(char *buffer, unsigned int nbChar)
{
    //Number of bytes we'll have read
    DWORD bytesRead;
    //Number of bytes we'll really ask to read
    unsigned int toRead;

    //Use the ClearCommError function to get status info on the Serial port
    ClearCommError(this->hSerial, &this->errors, &this->status);

    //Check if there is something to read
    if (this->status.cbInQue>0)
    {
        //If there is we check if there is enough data to read the required number
        //of characters, if not we'll read only the available characters to prevent
        //locking of the application.
        if (this->status.cbInQue>nbChar)
        {
            toRead = nbChar;
        }
        else
        {
            toRead = this->status.cbInQue;
        }

        //Try to read the require number of chars, and return the number of read bytes on success
        if (ReadFile(this->hSerial, buffer, toRead, &bytesRead, NULL))
        {
            return bytesRead;
        }

    }

    //If nothing has been read, or that an error was detected return 0
    return 0;

}

bool Serial::writeData(char * buffer, unsigned int nbChar)
{
    DWORD bytesSend;
    //Try to write the buffer on the Serial port
    if (!WriteFile(this->hSerial, (void *)buffer, nbChar, &bytesSend, 0))
    {
        //In case it don't work get comm error and return false
        ClearCommError(this->hSerial, &this->errors, &this->status);

        return false;
    }
    else
    {
        //strcat(storeData, buffer);//store the buffer into an array
        //strcat(storeData, " ");//store with space too
        return true;
    }
}

bool Serial::isConnected()
{
    //Simply return the connection status
    return this->connected;
}

//to write xyz
void Serial::writeXYZ(char x[], char y[], char z[])
{
    int length = 4;
    if(writeData(x, length) == true)
    {
        if(writeData(y, length) == true)
        {
            if(writeData(z, length) == true)
            {
                cout << "X,Y and Z is written to arduino.\n";
            }
            else
                cout << "Z unable to be written.\n";
        }
        else
            cout << "Y unable to be written.\n";
    }
    else
        cout << "X unable to be written.\n";
}

void Serial::compareData(char receiveData[])
{
    char * seperate1, *seperate2;
    int counter = 0;
    bool complete1 = false, complete2 = false;
    string x1, x2, y1, y2, z1, z2;
    seperate1 = strtok(receiveData, " ");
    while(seperate1 != NULL)
    {
        if(counter == 0)//1st seperated value
        {
            x1 = seperate1;
            counter++;//increment counter
        }
        else if(counter == 1)//2nd seperated value
        {
            y1 = seperate1;
            counter++;//increment counter
        }
        else if(counter == 2)//3rd seperated value
        {
            z1 = seperate1;
            counter = 0;//reset counter
        }
        seperate1 = strtok(NULL, " ");
        complete1 = true;


    }

    seperate2 = strtok(storeData, " ");

    while(seperate2 != NULL)
    {
        if(counter == 0)//1st seperated value
        {
            x2 = seperate2;
            counter++;//increment counter
        }
        else if(counter == 1)//2nd seperated value
        {
            y2 = seperate2;
            counter++;//increment counter
        }
        else if(counter == 2)//3rd seperated value
        {
            z2 = seperate2;
            counter = 0;//reset counter
        }
        seperate2 = strtok(NULL, " ");
        complete2 = true;
    }

    //compare write value with read value
    if(complete1 == true && complete2 == true)
    {
        if(x1 == x2)
        {
            if(y1 == y2)
            {
                if(z1 == z2)
                {
                    cout << "X,Y and Z values are the same.\n";//if all same then print out a successful message
                    cout << "X1: "<< x1 << " X2: " << x2 << endl << "Y1: " << y1 << " Y2: " << y2 << endl << "Z1: " << z1 << " Z2: " << z2 << endl;
                    sendCoordinates(x1, y1, z1);
                }
                else
                {
                    cout << "X1: "<< x1 << " X2: " << x2 << endl << "Y1: " << y1 << " Y2: " << y2 << endl << "Z1: " << z1 << " Z2: " << z2 << endl;
                    cout << "Z value is not same.\n";

                }
            }
            else
            {
                cout << "X1: "<< x1 << " X2: " << x2 << endl << "Y1: " << y1 << " Y2: " << y2 << endl << "Z1: " << z1 << " Z2: " << z2 << endl;
                cout << "Y value is not same.\n";

            }
        }
        else
        {
            cout << "X1: "<< x1 << " X2: " << x2 << endl << "Y1: " << y1 << " Y2: " << y2 << endl << "Z1: " << z1 << " Z2: " << z2 << endl;
            cout << "X value is not same.\n";

        }
    }

}

void Serial::sendCoordinates(string x, string y, string z)
{
    Coordinates value;
    value.xCoordinate = x;
    value.yCoordinate = y;
    value.zCoordinate = z;
    cout << value.xCoordinate << " " << value.yCoordinate << " " << value.zCoordinate << endl;
    //emited
}




