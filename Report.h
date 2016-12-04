#ifndef __REPORT_H__
#define __REPORT_H__

#include <string>
#include <QObject>
#include <QDebug>
#include <QProcess>
#include "tinyxml2.h"


using namespace std;
using namespace tinyxml2;

class Report : public QObject
{
    Q_OBJECT

    private:
        tinyxml2::XMLDocument doc;
        bool IsDigitString(const string&);
        bool ValidateUptime(const char*);
        bool ValidateXMLContent();
        bool ValidateDate(const char*);
        bool isTimestampExist(const string&);

    public:
        Report() {}
        bool LoadXMLFile(const char*);
        bool DisplayAllTimestamp();
        bool DeleteTimestamp(const string&);

    public slots:
        bool displaySpecificTimestamp(QString);
        bool generateMasterReport(QString);
        bool updateTimestamp(QString, int, int);
        bool saveXMLFile(QString);

    signals:
        void sendTimestampData(QString processed, QString uptime, QString errorCount);
};

#endif // __REPORT_H__
