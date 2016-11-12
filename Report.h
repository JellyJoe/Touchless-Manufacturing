#ifndef __REPORT_H__
#define __REPORT_H__

#include <string>
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class Report
{
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
//        bool AddTimestamp(); // change according to data obtained from arm
        bool DisplaySpecificTimestamp(const string&);
        bool DisplayAllTimestamp();
        bool DeleteTimestamp(const string&);

};

#endif // __REPORT_H__
