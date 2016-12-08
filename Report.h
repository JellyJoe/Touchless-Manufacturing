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
        bool isDigitString(const string&);
        bool isTimestampExist(const string&);
        bool validateUptime(const char*);
        bool validateXMLContent();
        bool validateDate(const char*);

    public:
        Report() {}
        bool loadXMLFile(const char*);

    public slots:
        bool displaySpecificTimestamp(QString);
        bool generateMasterReport(QString);
        bool updateTimestamp(QString, int, int);
        bool saveXMLFile(QString);

    signals:
        void sendTimestampData(const QString &processed, const QString &uptime, const QString &errorCount);
};

#endif // __REPORT_H__
