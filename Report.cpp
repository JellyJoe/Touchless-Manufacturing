#include <iostream>
#include <fstream>
#include "Report.h"

bool Report::IsDigitString(const string& number)
{
    return number.find_first_not_of("0123456789") == string::npos;
}

bool Report::ValidateDate(const char* date)
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

    // the second "-" should not be the last character in the date string
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

    // validates the days against months
    switch(month_int)
    {
        case 2: if(day_int > 29) // february does not have more than 29 days
                    return false;
                else if(day_int == 29 && is_leap_year == false) // only leap years have 29 days
                    return false;
                break;

        case 4: if(day_int > 30) // april does not have more than 30 days
                    return false;
                break;

        case 6: if(day_int > 30) // june does not have more than 30 days
                    return false;
                break;

        case 9: if(day_int > 30) // september does not have more than 30 days
                    return false;
                break;

        case 11:if(day_int > 30) // november does not have more than 30 days
                    return false;
                break;
    }

    return true; // if all validations pass, returns true
}

bool Report::ValidateUptime(const char* uptime)
{
    if(uptime == NULL)
        return false;

    string uptime_string(uptime);

    int minute_int, second_int;
    size_t first_colon_position, second_colon_position, third_colon_check;
    string hour_string, minute_string, second_string;

    // looks for the first ":" in the uptime string, then checks to see if it is found or not
    first_colon_position = uptime_string.find(":");
    if(first_colon_position == string::npos)
        return false;

    // if the first ":" is the first character in the string, this means there is no hour input
    if(first_colon_position == 0)
        return false;

    // look for the second ":" in the uptime string, and checks to see if it is found or not
    second_colon_position = uptime_string.find(":", first_colon_position + 1);
    if(second_colon_position == string::npos)
        return false;

    // checks to see if the first ":" and the second ":" are next to each other or not
    // if it is, that means that there is no minute input
    if(first_colon_position + 1 == second_colon_position)
        return false;

    // checks to see if there are any extra ":" in the uptime string
    third_colon_check = uptime_string.find(":", second_colon_position + 1);
    if(third_colon_check != string::npos)
        return false;

    // the second ":" should not be the last character in the string
    // this would mean that there is no second input
    if(second_colon_position == (uptime_string.length() - 1))
        return false;

    // extracts the hour input from the uptime string
    hour_string = uptime_string.substr(0, first_colon_position);

    // checks if the hour input is a string that contains digits only
    if(IsDigitString(hour_string) == false)
        return false;

    // extracts the minute input from the uptime string
    minute_string = uptime_string.substr(first_colon_position + 1, (second_colon_position - (first_colon_position + 1)));

    // checks if the minute input is a string that contains digits only
    if(IsDigitString(minute_string) == false)
        return false;

    // converts the minute string into an integer variable
    minute_int = atoi(minute_string.c_str());

    // minutes cannot be more than 59
    if(minute_int > 59)
        return false;

    // extracts the second input from the uptime string
    second_string = uptime_string.substr(second_colon_position + 1);

    // checks if the second input is a string that contains digits only
    if(IsDigitString(second_string) == false)
        return false;

    // converts the second string into an integer variable
    second_int = atoi(second_string.c_str());

    // seconds cannot be more than 59
    if(second_int > 59)
        return false;

    return true; // returns true if all validations pass
}

bool Report::ValidateXMLContent()
{
    if(doc.RootElement() == NULL)
        return false;

    const XMLElement* arm = doc.FirstChildElement(); // sets the first root element
    const XMLElement* timestamp = NULL;
    const XMLElement* processed = NULL;
    const XMLElement* uptime = NULL;
    const XMLElement* errors = NULL;
    const XMLElement* error = NULL;
    const XMLElement* element_validate = NULL;

    int attribute_count = 0;

    // checks to see if the root element is named "arm"
    if(strcmp(arm->Value(), "arm") != 0)
        return false;

    // there should not be any text in the root element "arm"
    if(arm->GetText() != NULL)
        return false;

    // root element "arm" must have an attribute called "id"
    if(arm->Attribute("id") == NULL)
        return false;

    // resets the attribute counter
    // loops through the element and counts the number of attributes found
    // since attribute "id" was found, there can only be at most one attribute
    attribute_count = 0;
    for(const XMLAttribute* attribute = arm->FirstAttribute(); attribute; attribute = attribute->Next())
        attribute_count++;

    // there cannot be more than 1 attribute in the root element "arm"
    if(attribute_count > 1)
        return false;

    // gets the first "timestamp" child element from the root element "arm"
    timestamp = arm->FirstChildElement();

    // if there is at least one element in the root element "arm"
    if(timestamp != NULL)
    {
        while(timestamp != NULL) // while loop that iterates through each element in the root element "arm"
        {
            // checks to see if the element is named "timestamp"
            if(strcmp(timestamp->Value(), "timestamp") != 0)
                return false;

            // the timestamp element should not have any text
            if(timestamp->GetText() != NULL)
                return false;

            // the "timestamp" element must have an attribute called "date"
            if(timestamp->Attribute("date") == NULL)
                return false;

            // resets the attribute counter
            // loops through the element and counts the number of attributes found
            // since attribute "date" was found, there can only be at most one attribute
            attribute_count = 0;
            for(const XMLAttribute* attribute = timestamp->FirstAttribute(); attribute; attribute = attribute->Next())
                attribute_count++;

            // there cannot be more than 1 attribute in the element "timestamp"
            if(attribute_count > 1)
                return false;

            // validates the value in the attribute "date"
            if(ValidateDate(timestamp->Attribute("date")) == false)
                return false;

            // since element "timestamp" has been validated, it will move to the elements in it
            // sets the first element in the element "timestamp"
            processed = timestamp->FirstChildElement();
            if(processed == NULL) // there cannot be no elements in the "timestamp" element
                return false;

            // the first element name inside of element "timestamp" should be "processed"
            if(strcmp(processed->Value(), "processed") != 0)
                return false;

            // the "processed" element should not have any text
            if(processed->GetText() != NULL)
                return false;

            // the "processed" element should have the attribute "value"
            if(processed->Attribute("value") == NULL)
                return false;

            // resets the attribute counter
            // loops through the element and counts the number of attributes found
            // since attribute "value" was found, there can only be at most one attribute
            attribute_count = 0;
            for(const XMLAttribute* attribute = processed->FirstAttribute(); attribute; attribute = attribute->Next())
                attribute_count++;

            // there cannot be more than 1 attribute in the element "processed"
            if(attribute_count > 1)
                return false;

            // sets the value of the attribute "value" into a string
            string processed_value_string(processed->Attribute("value"));

            // the value in the attribute "value" cannot be empty
            if(processed_value_string.empty())
                return false;

            // checks to see if the value are digits only
            if(IsDigitString(processed_value_string) == false)
                return false;

            // checks if there are any elements in the element "processed"
            element_validate = processed->FirstChildElement();
            if(element_validate != NULL) // there should not be any elements inside the element "processed"
                return false;

            // since element "processed" is validated, it will move to it's sibling element
            uptime = processed->NextSiblingElement();
            if(uptime == NULL) // there must be an element "uptime"
                return false;

            // checks to see if the element name is "uptime"
            if(strcmp(uptime->Value(), "uptime") != 0)
                return false;

            // the "uptime" element should not have any text
            if(uptime->GetText() != NULL)
                return false;

            // "uptime" element should havee an attribute "value"
            if(uptime->Attribute("value") == NULL)
                return false;

            // resets the attribute counter
            // loops through the element and counts the number of attributes found
            // since attribute "value" was found, there can only be at most one attribute
            attribute_count = 0;
            for(const XMLAttribute* attribute = uptime->FirstAttribute(); attribute; attribute = attribute->Next())
                attribute_count++;

            // there cannot be more than 1 attribute in the element "uptime"
            if(attribute_count > 1)
                return false;

            // validates the value of the attribute "value" from the element "uptime"
            if(ValidateUptime(uptime->Attribute("value")) == false)
                return false;

            // the element "uptime" should not have any elements inside it
            element_validate = uptime->FirstChildElement();
            if(element_validate != NULL)
                return false;

            // since the "uptime" element is validated, it will move to it's sibling element
            errors = uptime->NextSiblingElement();
            if(errors == NULL) // there must be an element called "errors"
                return false;

            // checks to see if the element name is "errors"
            if(strcmp(errors->Value(), "errors") != 0)
                return false;

            // the "errors" element should not have any text
            if(errors->GetText() != NULL)
                return false;

            // checks to see if there is an attribute named "count"
            if(errors->Attribute("count") == NULL)
                return false;

            // resets the attribute counter
            // loops through the element and counts the number of attributes found
            // since attribute "count" was found, there can only be at most one attribute
            attribute_count = 0;
            for(const XMLAttribute* attribute = errors->FirstAttribute(); attribute; attribute = attribute->Next())
                attribute_count++;

            // there cannot be more than 1 attribute in the element "errors"
            if(attribute_count > 1)
                return false;

            // convert the attribute value into a string
            string error_count_string(errors->Attribute("count"));

            // value of attribute "count" cannot be empty
            if(error_count_string.empty())
                return false;

            // checks to see if the value of attribute "count" contains only digits
            if(IsDigitString(error_count_string) == false)
                return false;

            // converts the "count" value into an integer
            int error_count_int = atoi(error_count_string.c_str());

            // gets the first child element from the "errors" element
            error = errors->FirstChildElement();

            // if there are no error counts but there is an element in the element "errors"
            if(error_count_int == 0 && error != NULL)
                return false;

            // iterates through each error in the element "errors"
            for(int i = 0; i < error_count_int; i++)
            {
                if(error == NULL) // if there is at least one error count but there is no element
                    return false;

                // checks if the element name is called "error"
                if(strcmp(error->Value(), "error") != 0)
                    return false;

                // the element "error" must have text in it
                if(error->GetText() == NULL)
                    return false;

                // resets the attribute counter
                // loops through the element and counts the number of attributes found
                attribute_count = 0;
                for(const XMLAttribute* attribute = error->FirstAttribute(); attribute; attribute = attribute->Next())
                    attribute_count++;

                // there cannot be more than 0 attribute in the element "error"
                if(attribute_count > 0)
                    return false;

                // element "error" cannot have any child element
                element_validate = error->FirstChildElement();
                if(element_validate != NULL)
                    return false;

                error = error->NextSiblingElement();
            }

            // checks to see if there are any more sibling elements after errors
            element_validate = errors->NextSiblingElement();
            if(element_validate != NULL) // element "errors" should be the last element
                return false;

            // goes to the next "timestamp" element
            timestamp = timestamp->NextSiblingElement();
        }
    }

    // only one root element "arm" can be present
    arm = arm->NextSiblingElement();
    if(arm != NULL)
        return false;

    return true; // returns true, if all validations pass
}

// DisplayAllTimestamp() returns false if it does not have any data to read, else it will return true
bool Report::DisplayAllTimestamp()
{
    if(doc.RootElement() == NULL) // checks if the user has ran LoadXMLFile() once or not
        return false;

    const XMLElement* arm = doc.FirstChildElement();

    cout << "Arm ID: " << arm->Attribute("id") << endl;

    const XMLElement* timestamp = arm->FirstChildElement("timestamp");
    const XMLElement* processed = NULL;
    const XMLElement* uptime = NULL;
    const XMLElement* errors = NULL;
    const XMLElement* error = NULL;

    if(timestamp == NULL)
    {
        cout << endl << "No records." << endl;
        return true;
    }

    while(timestamp != NULL) // iterates through every timestamp and displays the data
    {
        cout << endl << "Timestamp: " << timestamp->Attribute("date") << endl;

        processed = timestamp->FirstChildElement("processed");
        cout << "Processed: " << processed->Attribute("value") << endl;

        uptime = processed->NextSiblingElement("uptime");
        cout << "Uptime: " << uptime->Attribute("value") << endl;

        errors = uptime->NextSiblingElement("errors");
        cout << "Error count: " << errors->Attribute("count") << endl;

        int error_count_int = errors->IntAttribute("count");
        error = errors->FirstChildElement("error");
        for(int i = 0; i < error_count_int; i++)
        {
            cout << "Error message " << i + 1 << ": " << error->GetText() << endl;
            error = error->NextSiblingElement("error");
        }

        timestamp = timestamp->NextSiblingElement("timestamp");
    }

    return true;
}

// AddTimestamp() currently has fixed data that it adds as a demo of the function
// This function is to be modified when implementing to the user interface
// returns false if user has not ran LoadXMLFile(), else it will return true
//bool Report::AddTimestamp()
//{
//    if(doc.RootElement() == NULL)
//        return false;

//    int error_count_int = 2;

//    XMLElement* arm = doc.FirstChildElement();
//    XMLElement* timestamp = doc.NewElement("timestamp");
//    XMLElement* processed = doc.NewElement("processed");
//    XMLElement* uptime = doc.NewElement("uptime");
//    XMLElement* errors = doc.NewElement("errors");

//    timestamp->SetAttribute("date", "12-5-2016");
//    processed->SetAttribute("value", 32);
//    uptime->SetAttribute("value", "11:22:33");
//    errors->SetAttribute("count", error_count_int);

//    if(error_count_int > 0)
//    {
//        XMLElement* error[error_count_int] = {NULL};
//        for(int i = 0; i < error_count_int; i++)
//        {
//            error[i] = doc.NewElement("error");
//            error[i]->SetText(i + 1);
//            errors->InsertEndChild(error[i]);
//        }
//    }

//    timestamp->InsertEndChild(processed);
//    timestamp->InsertEndChild(uptime);
//    timestamp->InsertEndChild(errors);
//    arm->InsertEndChild(timestamp);

//    return true;
//}

// SaveXMLFile() saves the current XMLDocument into the file XML_STORAGE_FILENAME
// returns false if user has not ran LoadXMLFile() before or it encountered an error saving the file
bool Report::SaveXMLFile(const char* XML_STORAGE_FILENAME)
{
    if(doc.RootElement() == NULL)
        return false;

    if(doc.SaveFile(XML_STORAGE_FILENAME) != 0)
        return false;

    return true;
}

// LoadXMLFile() loads the file XML_STORAGE_FILENAME and validates the content
// returns false if it encounters any error loading the file or the content does not pass validation test
bool Report::LoadXMLFile(const char* XML_STORAGE_FILENAME)
{
    if(doc.LoadFile(XML_STORAGE_FILENAME) != 0)
        return false;

    if(ValidateXMLContent() == false)
        return false;

    return true;
}

// DisplaySpecificTimestamp() takes in a date format and displays the timestamps data
// returns false if LoadXMLFile() has not been used or if date format is not valid
bool Report::displaySpecificTimestamp(QString qDate)
{
    string date = qDate.toLocal8Bit().constData();

    if(doc.RootElement() == NULL)
        return false;

    if(ValidateDate(date.c_str()) == false)
        return false;

    XMLElement* timestamp = doc.FirstChildElement()->FirstChildElement();
    XMLElement* processed = NULL;
    XMLElement* uptime = NULL;
    XMLElement* errors = NULL;
//    XMLElement* error = NULL;

    while(timestamp != NULL) // iterates through the whole timestamp record
    {
        if(strcmp(timestamp->Attribute("date"), date.c_str()) == 0) // if the date matches the timestamp
        {
            processed = timestamp->FirstChildElement("processed");
//            cout << "Processed: " << processed->Attribute("value") << endl;

            uptime = processed->NextSiblingElement("uptime");
//            cout << "Uptime: " << uptime->Attribute("value") << endl;

            errors = uptime->NextSiblingElement("errors");
//            cout << "Error count: " << errors->Attribute("count") << endl;

//            int error_count_int = errors->IntAttribute("count");
//            error = errors->FirstChildElement("error");
//            for(int i = 0; i < error_count_int; i++)
//            {
//                cout << "Error message " << i + 1 << ": " << error->GetText() << endl;
//                error = error->NextSiblingElement("error");
//            }

            QString processedQString = QString::fromUtf8(processed->Attribute("value"));
            QString uptimeQString = QString::fromUtf8(uptime->Attribute("value"));
            QString countQString = QString::fromUtf8(errors->Attribute("count"));

            emit sendTimestampData(processedQString, uptimeQString, countQString);
            return true;
        }

        timestamp = timestamp->NextSiblingElement();
    }

    emit sendTimestampData("nil", "nil", "nil");
//    cout << "No record found for timestamp" << endl;

    return true;
}

// DeleteTimestamp() takes in a string date and deletes the record with the date timestamp
// returns false if user has not ran LoadXMLFile() once or if date format is not valid
bool Report::DeleteTimestamp(const string& date)
{
    if(doc.RootElement() == NULL)
        return false;

    if(ValidateDate(date.c_str()) == false)
        return false;

    XMLElement* arm = doc.FirstChildElement();
    XMLElement* timestamp = arm->FirstChildElement();

    while(timestamp != NULL) // iterates through the whole timestamp record
    {
        if(strcmp(timestamp->Attribute("date"), date.c_str()) == 0) // if date matches the record timestamp
        {
            arm->DeleteChild(timestamp);

            cout << "Deleted timestamp record \"" << date << "\"" << endl;

            return true;
        }

        timestamp = timestamp->NextSiblingElement();
    }

    cout << "No record found to delete for timestamp \"" << date << "\"" << endl;

    return true;
}

bool Report::generateMasterReport(QString q_EXCEL_TEMPLATE_FILENAME)
{
    string EXCEL_TEMPLATE_FILENAME = q_EXCEL_TEMPLATE_FILENAME.toLocal8Bit().constData();

    if(doc.RootElement() == NULL) // if user has not ran LoadXMLFile()
        return false;

    XMLDocument excelDoc;
    if(excelDoc.LoadFile(EXCEL_TEMPLATE_FILENAME.c_str()) != 0) // loads the Excel Template file
        return false;

    XMLElement* workbook = excelDoc.FirstChildElement("Workbook");
    if(workbook == NULL)
        return false;

    XMLElement* worksheet = workbook->FirstChildElement("Worksheet");
    if(worksheet == NULL)
        return false;

    XMLElement* table = worksheet->FirstChildElement("Table");
    if(table == NULL)
        return false;

    for(int i = 0; i < 2; i++) // sets the first two row of the Excel file
    {
        XMLElement* row = excelDoc.NewElement("Row");
        XMLElement* cell = excelDoc.NewElement("Cell");
        XMLElement* data = excelDoc.NewElement("Data");

        if(i == 0) // merged 4 columns and have a text of "Arm"
        {
            cell->SetAttribute("ss:MergeAcross", 3);
            cell->SetAttribute("ss:StyleID", "s63");
            data->SetAttribute("ss:Type", "String");
            data->SetText("Arm");

            cell->InsertEndChild(data);
            row->InsertEndChild(cell);
            table->InsertEndChild(row);
        }
        else if(i == 1) // sets the second row of the excel file
        {
            for(int j = 0; j < 4; j++) // iterates through each column
            {
                cell = excelDoc.NewElement("Cell");
                data = excelDoc.NewElement("Data");
                data->SetAttribute("ss:Type", "String");

                if(j == 0) // set the text of each column
                    data->SetText("Date");
                else if(j == 1)
                    data->SetText("Processed");
                else if(j == 2)
                    data->SetText("Uptime");
                else
                    data->SetText("Error Message");

                cell->InsertEndChild(data);
                row->InsertEndChild(cell);
            }
            table->InsertEndChild(row);
        }
    }

    // declaration of arm data storage variables
    XMLElement* arm = doc.FirstChildElement();
    const XMLElement* timestamp = arm->FirstChildElement("timestamp");
    const XMLElement* processed = NULL;
    const XMLElement* uptime = NULL;
    const XMLElement* errors = NULL;
    const XMLElement* error = NULL;

    if(timestamp ==  NULL) // no records
        return false;

    while(timestamp != NULL) // iterates through every record
    {
        // declaration of excel document elements
        XMLElement* row = excelDoc.NewElement("Row");
        XMLElement* cell = excelDoc.NewElement("Cell");
        XMLElement* data = excelDoc.NewElement("Data");

        // retrieves the data from the arm data storage file
        processed = timestamp->FirstChildElement("processed");
        uptime = processed->NextSiblingElement("uptime");
        errors = uptime->NextSiblingElement("errors");
        error = NULL;

        for(int i = 0; i < 4; i++) // set the arm data into each of their columns
        {
            cell = excelDoc.NewElement("Cell");
            data = excelDoc.NewElement("Data");

            if(i == 0) // sets the date data into the first column
            {
                data->SetText(timestamp->Attribute("date"));
                data->SetAttribute("ss:Type", "String");
                cell->InsertEndChild(data);
                row->InsertEndChild(cell);
            }
            else if(i == 1) // sets the processed value into the second column
            {
                data->SetText(processed->Attribute("value"));
                data->SetAttribute("ss:Type", "Number");
                cell->InsertEndChild(data);
                row->InsertEndChild(cell);
            }
            else if(i == 2) // sets the uptime value to the third column
            {
                data->SetText(uptime->Attribute("value"));
                data->SetAttribute("ss:Type", "String");
                cell->InsertEndChild(data);
                row->InsertEndChild(cell);
            }
            else // sets the error message on the last column
            {
                int error_count_int = errors->IntAttribute("count");
                error = errors->FirstChildElement("error");
                if(error_count_int == 0) // if there are no errors from the date
                {
                    data->SetAttribute("ss:Type", "String");
                    data->SetText("Nil");
                    cell->InsertEndChild(data);
                    row->InsertEndChild(cell);
                    table->InsertEndChild(row);
                }
                else // at least one error was found in the date
                {
                    for(int j = 0; j < error_count_int; j++) // iterates through each errors
                    {
                        if(j == 0) // if it is the first error message, it will be on the same row as the other data
                        {
                            data->SetAttribute("ss:Type", "String");
                            data->SetText(error->GetText());
                            cell->InsertEndChild(data);
                            row->InsertEndChild(cell);
                            table->InsertEndChild(row);
                        }
                        else // if it is not the first error message, it will be below the previous error message
                        {
                            row = excelDoc.NewElement("Row");
                            cell = excelDoc.NewElement("Cell");
                            data = excelDoc.NewElement("Data");
                            cell->SetAttribute("ss:Index", "4");
                            data->SetAttribute("ss:Type", "String");
                            data->SetText(error->GetText());
                            cell->InsertEndChild(data);
                            row->InsertEndChild(cell);
                            table->InsertEndChild(row);
                        }
                        error = error->NextSiblingElement("error");
                    }
                }
            }
        }

        // Adds an empty merged cell under a timestamp record
        row = excelDoc.NewElement("Row");
        cell = excelDoc.NewElement("Cell");
        data = excelDoc.NewElement("Data");
        cell->SetAttribute("ss:MergeAcross", 3);
        cell->SetAttribute("ss:StyleID", "s63");
        data->SetAttribute("ss:Type", "String");
        cell->InsertEndChild(data);
        row->InsertEndChild(cell);
        table->InsertEndChild(row);

        timestamp = timestamp->NextSiblingElement("timestamp"); // goes to the next timestamp
    }

    if(excelDoc.SaveFile("MasterReport.temp") != 0) // fails to save the excel document
        return false;

    string temp;
    ofstream masterFileStream;
    masterFileStream.open("MasterReport.xml");
    if(!masterFileStream) // file not found or cannot be opened
        return false;

    ifstream tempFileStream;
    tempFileStream.open("MasterReport.temp");
    if(!tempFileStream) // file not found or cannot be opened
        return false;

    masterFileStream << "<?xml version=\"1.0\"?>" << endl;
    masterFileStream << "<?mso-application progid=\"Excel.Sheet\"?>" << endl;

    getline(tempFileStream, temp); // removes the first line from the temp file
    while(!tempFileStream.eof()) // dumps all the remaining lines from the temp file into the master file
    {
        getline(tempFileStream, temp);
        masterFileStream << temp << endl;
    }

    masterFileStream.close();
    tempFileStream.close();

    return true;
}
