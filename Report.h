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

    public:
        Report() {}
        bool ValidateDate(const char*);
        bool LoadXMLFile(const char*);
        bool SaveXMLFile(const char*);
        //bool AddTimestamp(); // change according to data obtained from arm

        bool DisplayAllTimestamp();
        bool DeleteTimestamp(const string&);

    public slots:
        bool displaySpecificTimestamp(QString);
        /*void handleSubmitTextField(const QString& in){
            qDebug() << "c++: HandleTextField::handleSubmitTextField:" << in;

            QString message = "checking";

            emit setTextField(message);
        }*/

    signals:
        //void setTextField(QVariant text);


};

#endif // __REPORT_H__
