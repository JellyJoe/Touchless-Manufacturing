
Arm::Arm(QObject *parent) :
    QObject(parent)
{
    ArmSp = new Serial((char*)"COM6");    // adjust as needed

    if (ArmSp->IsConnected())
    {
        std::cout << "Arm is connected" << endl;
    }
    else
    {

        std::cout << "Arm couldn't connect" << endl;

    }

    outgoingData[256] = "";
    incomingData[256] = "";
    dataLength = 256;
    cycle = 0;

}


void Arm::demoClicked()
{

    strcpy(outgoingData,"a");
    SP->WriteData(outgoingData,dataLength);
    Sleep(500);
    strcpy(outgoingData,"1");
    SP->WriteData(outgoingData,dataLength);
    Sleep(1000);

}

void Arm::manualLuanched()
{
    strcpy(outgoingData,"2");
    ArmSp->WriteData(outgoingData,dataLength);
}

void Arm::saveWithPump()
{
    strcpy(outgoingData,"s");
    ArmSp->WriteData(outgoingData,dataLength);
}

void Arm::saveWithoutPump()
{
    strcpy(outgoingData,"o");
    ArmSp->WriteData(outgoingData,dataLength);
}

void Arm::executeManualMovement()
{
    strcpy(outgoingData,"d");
    ArmSp->WriteData(outgoingData,dataLength);

}

void Arm::setPositionA()
{
    strcpy(outgoingData,"A");
    ArmSp->WriteData(outgoingData,dataLength);
}

void Arm::setPositionB()
{
    strcpy(outgoingData,"b");
    ArmSp->WriteData(outgoingData,dataLength);
}


void Arm::setPositionC()
{
    strcpy(outgoingData,"c");
    ArmSp->WriteData(outgoingData,dataLength);
}

void Arm::setHeight()
{
    strcpy(outgoingData,"h");
    ArmSp->WriteData(outgoingData,dataLength);
}

void Arm::executeAutoMovement()
{
    strcpy(outgoingData,"e");
    ArmSp->WriteData(outgoingData,dataLength);
    do
    {
        int result=0;
        result = ArmSp->ReadData(incomingData, dataLength);
        incomingData[result] = '\0';
    }
    while(incomingData[0]!='D');
    cycle++;
}

void Arm::stopMovement()
{
    delete ArmSp;
    ArmSp = new Serial((char*)"COM6");
}
