#ifndef __ARM_H__
#define __ARM_H__
//Header Files
#define MAX_OUTGOING_DATA_LENGTH 10;
#include <QObject>
#include <QDebug>
#include <QProcess>
#include "Serial.h"

//Arm Class
class Arm : public QObject
{
    //Inherits Qobject for QT signal and slots
    Q_OBJECT

//Private Data for the Arm Class
private:
    char outgoingData[MAX_OUTGOING_DATA_LENGTH];

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
    void stopMovement(); //Stop the Arm from moving
};

#endif // __ARM_H__
