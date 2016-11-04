#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "MyClass.h"
#include "Serial.h"
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <QtWidgets/QMessageBox>
#include <QDebug>


using namespace std;

int main(int argc, char *argv[])
{


    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));


    MyClass myClass;

    engine.rootContext()->setContextProperty("_myClass", &myClass);


    return app.exec();
}
