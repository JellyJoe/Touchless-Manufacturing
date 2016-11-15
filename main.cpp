#include <stdio.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <unistd.h>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtWidgets/QMessageBox>
#include <QDebug>

#include "MyClass.h"
#include "Serial.h"
#include "Report.h"
#include "Arm.h"

using namespace std;

const char XML_DATA_STORAGE[] = "C:\\Users\\Joe\\Documents\\Touchless-Manufacturing\\Arm_Data_Storage.xml";
//const char XML_DATA_STORAGE[] = "C:\\Users\\Sukhdip\\Documents\\TouchlessManufacturingApplication\\Arm_Data_Storage.xml";

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    Arm arm;
    engine.rootContext()->setContextProperty("_myArm", &arm);

    MyClass myClass;
    engine.rootContext()->setContextProperty("_myClass", &myClass);

    Report report;
    engine.rootContext()->setContextProperty("_report", &report);

    if(report.LoadXMLFile(XML_DATA_STORAGE) == true)
        qDebug() << "Successfully loaded XML file.";
    else
        qDebug() << "Failed to load XML file.";

    return app.exec();
}
