
Arm::Arm(QObject *parent) :
    QObject(parent)
{
    SP = new Serial((char*)"COM6");    // adjust as needed

    if (SP->IsConnected())
    {
        std::cout << "Arm is connected" << endl;
    }
    else
    {

        std::cout << "Arm couldn't connect" << endl;

    }

    outgoingData[256] = "";
    dataLength = 256;

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
