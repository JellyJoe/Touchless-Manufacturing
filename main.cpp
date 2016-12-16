#include <stdio.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtWidgets/QMessageBox>
#include <QDebug>

#include "Serial.h"
#include "Pixy.h"
#include "Report.h"
#include "Arm.h"

using namespace std;

const char XML_DATA_STORAGE[] = "Arm_Data_Storage.xml";

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    Arm arm;
    engine.rootContext()->setContextProperty("_myArm", &arm);

    Pixy pixy;
    engine.rootContext()->setContextProperty("_myPixy", &pixy);

    Report report;
    engine.rootContext()->setContextProperty("_myReport", &report);

    if(report.loadXMLFile(XML_DATA_STORAGE) == false)
    {
        qDebug() << "Failed to load XML file.";
    }
    else
    {
        qDebug() << "Successfully loaded XML file.";
    }

    return app.exec();
}
