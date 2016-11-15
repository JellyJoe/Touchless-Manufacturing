#ifndef ARM_H
#define ARM_H

#include <QObject>
#include <QDebug>
#include <QProcess>
#include "Serial.h"

class Arm : public QObject
{
    Q_OBJECT

private:
    char outgoingData[256];
    int dataLength;

public:

    Serial* ArmSp;
    explicit Arm(QObject *parent = 0);

public slots:
    void demoClicked();
    void manualLaunched();
    void saveWithPump();
    void saveWithoutPump();
    void executeManualMovement();
    void stopMovement();
};

#endif // ARM_H
