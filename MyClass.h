#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>
#include <QDebug>

class MyClass : public QObject
{
    Q_OBJECT

public:

    explicit MyClass(QObject *parent = 0);
    void addition()
    {

    }

public slots:
    void buttonClicked() {
        qDebug() << "Called the C++ slot with message:";
    }
};

#endif // MYCLASS_H
