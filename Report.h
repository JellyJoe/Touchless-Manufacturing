#ifndef __REPORT_H__
#define __REPORT_H__

#include <string>
#include "TinyXML2.h"

using namespace std;
using namespace tinyxml2;

class Report
{
    private:
        Report() {}
        static XMLDocument doc;
        static bool IsDigitString(const string&);
        static bool ValidateUptime(const char*);
        static bool ValidateXMLContent();
    public:
        static bool ValidateDate(const char*);
        static bool LoadXMLFile(const char*);
        static bool SaveXMLFile(const char*);
        static bool AddTimestamp(const string&, const int&, const string&, const int&); // change according to data obtained from arm
        static bool DisplaySpecificTimestamp(const string&);
        static bool DisplayAllTimestamp();
        static bool DeleteTimestamp(const string&);
};

#endif // __REPORT_H__
