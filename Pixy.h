#ifndef PIXY_H
#define PIXY_H

#define MAX_DATA_LENGTH 256
#include <QObject>
#include <QDebug>
#include <QProcess>
#include "Serial.h"

class Pixy : public QObject
{
    Q_OBJECT

private:
    char incomingData[MAX_DATA_LENGTH];
    char outgoingData[MAX_DATA_LENGTH];
    int check;
    QString path;
    QProcess pixyProcess;

public:
    Serial * pixySP;
    explicit Pixy(QObject * parent = 0);

public slots:
    void getBlocks();//Execute pixy
    bool checkBlocks();//To check for receive blocks is true
    void executePixymon();//Execute PixyMon
    void stopPixy();//Stop Pixy

};

#endif // PIXY_H
