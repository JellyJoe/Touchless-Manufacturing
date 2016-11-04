#include <iostream>
#include <string>
#include <chrono>
#include <cstdlib>
#include "tinyxml2.h"

// validate processed and count value, what if it;s empty lol
// validate all attributes inside an element

using namespace std;
using namespace tinyxml2;

const char XML_STORAGE_FILENAME[] = "Arm_Data_Storage.xml";

bool IsDigitString(const string& number)
{
    return number.find_first_not_of("0123456789") == string::npos;
}

bool ValidateDate(const char* date)
{
    if(date == NULL)
        return false;

    string date_string(date);

    if(date_string.length() > 10) // longest date format is 10 characters. eg. 11-11-2011
        return false;

    int day_int, month_int, year_int, remainder;
    size_t first_dash_position, second_dash_position, third_dash_check;
    string day_string, month_string, year_string;
    bool is_leap_year;

    // looks for the first "-" in the date string, then checks to see if it is found or not
    first_dash_position = date_string.find("-");
    if(first_dash_position == string::npos)
        return false;

    // if the first "-" is the first character in the string, this means there is no day input
    if(first_dash_position == 0)
        return false;

    // look for the second "-" in the date string, and checks to see if it is found or not
    second_dash_position = date_string.find("-", first_dash_position + 1);
    if(second_dash_position == string::npos)
        return false;

    // checks to see if the first "-" and the second "-" are next to each other or not
    // if it is, that means that there is no month input
    if(first_dash_position + 1 == second_dash_position)
        return false;

    // checks to see if there are any extra "-" in the date string
    third_dash_check = date_string.find("-", second_dash_position + 1);
    if(third_dash_check != string::npos)
        return false;

    // the secong "-" should not be the last character in the date string
    // this would mean that there is no year input
    if(second_dash_position == (date_string.length() - 1))
        return false;

    // extracts the day input from the date string
    day_string = date_string.substr(0, first_dash_position);

    // checks if the day input is a string that contains digits only
    if(IsDigitString(day_string) == false)
        return false;

    // converts the day string into an integer variable
    day_int = atoi(day_string.c_str());

    // days are ranged from 1 - 31 only
    if(day_int < 1 || day_int > 31)
        return false;

    // extracts the month input from the date string
    month_string = date_string.substr(first_dash_position + 1, (second_dash_position - (first_dash_position + 1)));

    // checks if the month input is a string that contains digits only
    if(IsDigitString(month_string) == false)
        return false;

    // converts the month string into an integer variable
    month_int = atoi(month_string.c_str());

    // months are ranged from 1 - 12 only
    if(month_int < 1 || month_int > 12)
        return false;

    // extracts the year input from the date string
    year_string = date_string.substr(second_dash_position + 1);

    // checks if the year input is a string that contains digits only
    if(IsDigitString(year_string) == false)
        return false;

    // converts the year string into an integer variable
    year_int = atoi(year_string.c_str());

    // linux timestamp began at 00:00:00 on 1-1-1970, ends at 03:14:07 on 19-1-2038 (year 2038 problem)
    if(year_int < 1970 || year_int > 2037)
        return false;

    // validates the month "february", since it has different days if it is a leap year
    if(month_int == 2)
    {
        remainder = year_int % 4;
        if(remainder != 0) // a leap year does not have remainders after dividing by 4
            is_leap_year = false;
        else
        {
            remainder = year_int % 100;
            if(remainder != 0) // a leap year must be able to divide by both 100 and 400 without remainders
                is_leap_year = true;
            else
            {
                remainder = year_int % 400;
                if(remainder != 0) // it is not a leap year if there is no remainder for 100 but has remainder for 400
                    is_leap_year = false;
                else
                    is_leap_year = true;
            }
        }
    }

    switch(month_int)
    {
        case 2: if(day_int > 29)
                    return false;
                else if(day_int == 29 && is_leap_year == false)
                    return false;
                break;

        case 4: if(day_int > 30)
                    return false;
                break;

        case 6: if(day_int > 30)
                    return false;
                break;

        case 9: if(day_int > 30)
                    return false;
                break;

        case 11:if(day_int > 30)
                    return false;
                break;
    }

    return true;
}

bool ValidateUptime(const char* uptime)
{
    if(uptime == NULL)
        return false;

    string uptime_string(uptime);

    int minute_int, second_int;
    size_t first_colon_position, second_colon_position, third_colon_check;
    string hour_string, minute_string, second_string;

    first_colon_position = uptime_string.find(":");
    if(first_colon_position == string::npos)
        return false;

    if(first_colon_position == 0)
        return false;

    second_colon_position = uptime_string.find(":", first_colon_position + 1);
    if(second_colon_position == string::npos)
        return false;

    if(first_colon_position + 1 == second_colon_position)
        return false;

    third_colon_check = uptime_string.find(":", second_colon_position + 1);
    if(third_colon_check != string::npos)
        return false;

    if(second_colon_position == (uptime_string.length() - 1))
        return false;

    hour_string = uptime_string.substr(0, first_colon_position);
    if(IsDigitString(hour_string) == false)
        return false;

    minute_string = uptime_string.substr(first_colon_position + 1, (second_colon_position - (first_colon_position + 1)));
    if(IsDigitString(minute_string) == false)
        return false;

    minute_int = atoi(minute_string.c_str());
    if(minute_int > 59)
        return false;

    second_string = uptime_string.substr(second_colon_position + 1);
    if(IsDigitString(second_string) == false)
        return false;

    second_int = atoi(second_string.c_str());
    if(second_int > 59)
        return false;

    return true;
}

bool ValidateXMLContent(XMLDocument& doc)
{
    XMLElement* arm = doc.FirstChildElement();
    XMLElement* timestamp = NULL;
    XMLElement* processed = NULL;
    XMLElement* uptime = NULL;
    XMLElement* errors = NULL;
    XMLElement* error = NULL;
    XMLElement* element_validate = NULL;

    // checks to see if the root element is named "arm"
    if(strcmp(arm->Value(), "arm") != 0)
        return false;

    // there should not be any text in the root element "arm"
    if(arm->GetText() != NULL)
        return false;

    // root element "arm" must have an attribute called "id"
    if(arm->Attribute("id") == NULL)
        return false;

    // gets the first "timestamp" child element from the root element "arm"
    timestamp = arm->FirstChildElement();

    if(timestamp != NULL)
    {
        while(timestamp != NULL)
        {
            if(strcmp(timestamp->Value(), "timestamp") != 0)
                return false;

            if(timestamp->Attribute("date") == NULL)
                return false;

            if(ValidateDate(timestamp->Attribute("date")) == false)
                return false;

            processed = timestamp->FirstChildElement();
            if(processed == NULL)
                return false;

            if(strcmp(processed->Value(), "processed") != 0)
                return false;

            if(processed->Attribute("value") == NULL)
                return false;

            string processed_value_string(processed->Attribute("value"));
            if(processed_value_string.empty())
                return false;

            if(IsDigitString(processed_value_string) == false)
                return false;

            if(processed->GetText() != NULL)
                return false;

            element_validate = processed->FirstChildElement();
            if(element_validate != NULL)
                return false;

            uptime = processed->NextSiblingElement();
            if(uptime == NULL)
                return false;

            if(strcmp(uptime->Value(), "uptime") != 0)
                return false;

            if(uptime->Attribute("value") == NULL)
                return false;

            if(ValidateUptime(uptime->Attribute("value")) == false)
                return false;

            if(uptime->GetText() != NULL)
                return false;

            element_validate = uptime->FirstChildElement();
            if(element_validate != NULL)
                return false;

            // ERROR ELEMENT
            errors = uptime->NextSiblingElement();
            if(errors == NULL)
                return false;

            if(strcmp(errors->Value(), "errors") != 0)
                return false;

            if(errors->Attribute("count") == NULL)
                return false;

            string error_count_string(errors->Attribute("count"));
            if(error_count_string.empty())
                return false;

            if(IsDigitString(error_count_string) == false)
                return false;

            if(errors->GetText() != NULL)
                return false;

            int error_count_int = atoi(error_count_string.c_str());
            error = errors->FirstChildElement();

            if(error_count_int == 0 && error != NULL)
                return false;

            for(int i = 0; i < error_count_int; i++)
            {
                if(error == NULL)
                    return false;

                if(strcmp(error->Value(), "error") != 0)
                    return false;

                if(error->GetText() == NULL)
                    return false;

                element_validate = error->FirstChildElement();
                if(element_validate != NULL)
                    return false;

                error = error->NextSiblingElement();
            }

            timestamp = timestamp->NextSiblingElement();
        }
    }

    // only one root element "arm" can be present
    arm = arm->NextSiblingElement();
    if(arm != NULL)
        return false;

    return true;
}

int main()
{
    // auto start_time = chrono::high_resolution_clock::now();

    // XMLDocument doc;
    // doc.LoadFile("test.xml");
    //
    // XMLElement* arm = doc.FirstChildElement();
    //
    // cout << "ID: " << arm->Attribute("id") << endl;
    //
    // XMLElement* timestamp = arm->FirstChildElement("timestamp");
    // XMLElement* element = NULL;
    // XMLElement* error = NULL;
    //
    // while(timestamp != NULL)
    // {
    //     cout << "---" << endl;
    //     cout << "Timestamp: " << timestamp->Attribute("date") << endl;
    //
    //     element = timestamp->FirstChildElement("processed");
    //     cout << "Processed: " << element->Attribute("value") << endl;
    //
    //     element = element->NextSiblingElement("uptime");
    //     cout << "Uptime: " << element->Attribute("value") << endl;
    //
    //     element = element->NextSiblingElement("errors");
    //     cout << "Error count: " << element->Attribute("count") << endl;
    //
    //     error = element->FirstChildElement("error");
    //     for(int i = 0; i < element->IntAttribute("count"); i++)
    //     {
    //         cout << error->GetText() << endl;
    //         error = error->NextSiblingElement("error");
    //     }
    //
    //     timestamp = timestamp->NextSiblingElement("timestamp");
    //     cout << "---" << endl;
    // }
    //
    // timestamp = doc.NewElement("timestamp");
    //
    // element = doc.NewElement("processed");
    // element->SetAttribute("value", "2");
    // timestamp->InsertEndChild(element);
    //
    // element = doc.NewElement("uptime");
    // element->SetAttribute("value", "11:22:33");
    // timestamp->InsertEndChild(element);
    //
    // element = doc.NewElement("errors");
    // element->SetAttribute("count", "1");
    //
    // error = doc.NewElement("error");
    // error->SetText("WEWEWEWEEEEEWEEWEWEWEWE");
    // element->InsertEndChild(error);
    // timestamp->InsertEndChild(element);
    //
    //
    // arm->InsertEndChild(timestamp);
    //
    //
    // doc.Print();


    // auto end_time = chrono::high_resolution_clock::now();
    // chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(end_time - start_time);
    // cout << "It took me " << time_span.count() << " seconds.";

    XMLDocument doc;
    doc.LoadFile("test.xml");

    if(doc.ErrorID() != 0)
    {
        cout << "Re-check \"" << XML_STORAGE_FILENAME << "\"" << endl;
        return 1;
    }

    if(ValidateXMLContent(doc) == true)
        cout << "XML content looks good." << endl;
    else
        cout << "Something fishy is in this XML content." << endl;

    return 0;
}
