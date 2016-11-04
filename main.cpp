#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "MyClass.h"

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
