#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>
#include <QDebug>
#include "Serial.h"

class MyClass : public QObject
{
    Q_OBJECT

private:


public:

    Serial* SP;

    explicit MyClass(QObject *parent = 0);
    void addition()
    {

    }

public slots:
    void buttonClicked() {
        qDebug() << "Called the C++ slot with message:";
    }

    void demoClicked();
};

#endif // MYCLASS_H
