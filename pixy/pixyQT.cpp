
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
    dataLength = 2;
}

void Pixy::getBlocks()
{
    int result = 0;
    result  = SP->readData(incomingData, dataLength);
    if(result != 0)
    {
        cout << incomingData << endl;
        for(int i = 0; i < sizeof(incomingData); i++)
        {
            incomingData[i] = '\0';
        }
    }
    Sleep(500);
}
