#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>
#include <QDebug>
#include <QProcess>
#include "Serial.h"

using namespace std;

class MyClass : public QObject
{
    Q_OBJECT

private:


public:

    explicit MyClass(QObject *parent = 0);


public slots:
    /*void buttonClicked() {
        qDebug() << "Called the C++ slot with message:";
    }*/

    void pixyRun();

};

#endif // MYCLASS_H
