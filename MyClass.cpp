#include "MyClass.h"
#include "Serial.h"
#include <iostream>
#include <QProcess>
#include <QDir>


MyClass::MyClass(QObject *parent) :
    QObject(parent)
{

}


void MyClass::pixyRun()
{

    qDebug() << "PixyMon run";
    //QString program = "C:\\Program Files (x86)\PixyMon\bin\PixyMon.exe";

    QProcess::execute("C:\\PixyMon\\bin\\PixyMon.exe");
    //QProcess::execute("\"C:\\Program Files (x86)\\PixyMon\\bin\\PixyMon.exe\"");
}


