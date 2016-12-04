
Pixy::Pixy(QObject * parent) :
    QObject(parent)
{
    pixySP = new Serial ((char*)"COM4");
    if(pixySP->isConnected())
    {
        std::cout << "Pixy is connected" << endl;
    }
    else
    {
        std::cout << "Pixy couldn't connect" << endl;
    }
    incomingData[2] = "";
    outgoingData[2] = "";
    dataLength = 2;
}

//Execute pixy by entering y
void Pixy::getBlocks()
{
    strcpy(outgoingData, "y");
    SP->WriteData(outgoingData, dataLength);
}

//Retrieve value from pixy and check if value receive is "T" means blocks detected and return true
//else return false
bool Pixy::checkBlocks()
{
    int result = 0;
    while(strcmp(outgoingData, "y") == 0)
    {
        result  = SP->ReadData(incomingData, dataLength);
        if(result != 0)
        {
            if(strcmp(incomingData, "T") == 0)
                return true;
            else
                return false;
        }
        Sleep(500);
    }
}
