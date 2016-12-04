#ifndef __ARM_H__
#define __ARM_H__
//Header Files
#define MAX_OUTGOING_DATA_LENGTH 10
#include <QObject>
#include <QDebug>
#include <QProcess>
#include <QTime>
#include "Serial.h"

//Arm Class
class Arm : public QObject
{
    //Inherits Qobject for QT signal and slots
    Q_OBJECT

//Private Data for the Arm Class
private:
    char outgoingData[MAX_OUTGOING_DATA_LENGTH];
    char incomingData[MAX_OUTGOING_DATA_LENGTH];
    int dataLength;
    int cycle;
    QTime currentTime;

//Public Data for the Arm Class
public:

    //Arm serial connection variable
    Serial* ArmSp;
    explicit Arm(QObject *parent = 0);

public slots:
    void demoClicked(); //Function that perform the demo feature
    void manualLaunched(); //Manual Launched Function
    void saveWithPump(); //Saving the Coordinates with Pump Enable
    void saveWithoutPump(); //Saving the Coordinates with Pump Enable
    void executeManualMovement(); //Executing Manual Movement
    void setPositionA();//Saving Position A
    void setPositionB();//Saving Position B
    void setPositionC();//Saving Position C
    void setHeight();//Saving Height of the Object
    void executeAutoMovement();
    void stopMovement(); //Stop the Arm from moving
    void executeTime(){currentTime.start();}//Start Process Time
    int getElapsedTime(){return currentTime.elapsed();}//Get Process Time
    int getCycle(){return cycle;}//Get Cycle Count
};

#endif // __ARM_H__
