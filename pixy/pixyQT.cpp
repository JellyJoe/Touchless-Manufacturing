
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
        outgoingData[256] = "";
        dataLength = 255;
    }

    void Pixy::getCoordinates()
    {
        strcpy(outgoingData, "Y");
        SP->WriteData(outgoingData, dataLength);
	

    }
