#include <iostream>
#include <fstream>
#include <sstream>
#include "Report.h"

//char MASTER_REPORT_FILENAME[] = "C:\\Users\\Joe\\Desktop\\MasterReport.xml";
char MASTER_REPORT_FILENAME[] = "C:\\Users\\Sukhdip\\Desktop\\MasterReport.xml";

bool Report::isDigitString(const string& number)
{
    return number.find_first_not_of("0123456789") == string::npos;
}

bool Report::validateDate(const char* date)
{
    if(date == NULL)
        return false;

    string dateString(date);

    if(dateString.length() > 10) // longest date format is 10 characters. eg. 11-11-2011
        return false;

    int dayInt, monthInt, yearInt, remainder;
    size_t firstDashPosition, secondDashPosition, thirdDashCheck;
    string dayString, monthString, yearString;
    bool isLeapYear = false;

    // looks for the first "-" in the date string, then checks to see if it is found or not
    firstDashPosition = dateString.find("-");
    if(firstDashPosition == string::npos)
        return false;

    // if the first "-" is the first character in the string, this means there is no day input
    if(firstDashPosition == 0)
        return false;

    // look for the second "-" in the date string, and checks to see if it is found or not
    secondDashPosition = dateString.find("-", firstDashPosition + 1);
    if(secondDashPosition == string::npos)
        return false;

    // checks to see if the first "-" and the second "-" are next to each other or not
    // if it is, that means that there is no month input
    if(firstDashPosition + 1 == secondDashPosition)
        return false;

    // checks to see if there are any extra "-" in the date string
    thirdDashCheck = dateString.find("-", secondDashPosition + 1);
    if(thirdDashCheck != string::npos)
        return false;

    // the second "-" should not be the last character in the date string
    // this would mean that there is no year input
    if(secondDashPosition == (dateString.length() - 1))
        return false;

    // extracts the day input from the date string
    dayString = dateString.substr(0, firstDashPosition);

    // checks if the day input is a string that contains digits only
    if(isDigitString(dayString) == false)
        return false;

    // converts the day string into an integer variable
    dayInt = atoi(dayString.c_str());

    // days are ranged from 1 - 31 only
    if(dayInt < 1 || dayInt > 31)
        return false;

    // extracts the month input from the date string
    monthString = dateString.substr(firstDashPosition + 1, (secondDashPosition - (firstDashPosition + 1)));

    // checks if the month input is a string that contains digits only
    if(isDigitString(monthString) == false)
        return false;

    // converts the month string into an integer variable
    monthInt = atoi(monthString.c_str());

    // months are ranged from 1 - 12 only
    if(monthInt < 1 || monthInt > 12)
        return false;

    // extracts the year input from the date string
    yearString = dateString.substr(secondDashPosition + 1);

    // checks if the year input is a string that contains digits only
    if(isDigitString(yearString) == false)
        return false;

    // converts the year string into an integer variable
    yearInt = atoi(yearString.c_str());

    // linux timestamp began at 00:00:00 on 1-1-1970, ends at 03:14:07 on 19-1-2038 (year 2038 problem)
    if(yearInt < 1970 || yearInt > 2037)
        return false;

    // validates the month "february", since it has different days if it is a leap year
    if(monthInt == 2)
    {
        remainder = yearInt % 4;
        if(remainder != 0) // a leap year does not have remainders after dividing by 4
            isLeapYear = false;
        else
        {
            remainder = yearInt % 100;
            if(remainder != 0) // a leap year must be able to divide by both 100 and 400 without remainders
                isLeapYear = true;
            else
            {
                remainder = yearInt % 400;
                if(remainder != 0) // it is not a leap year if there is no remainder for 100 but has remainder for 400
                    isLeapYear = false;
                else
                    isLeapYear = true;
            }
        }
    }

    // validates the days against months
    switch(monthInt)
    {
        case 2: if(dayInt > 29) // february does not have more than 29 days
                    return false;
                else if(dayInt == 29 && isLeapYear == false) // only leap years have 29 days
                    return false;
                break;

        case 4: if(dayInt > 30) // april does not have more than 30 days
                    return false;
                break;

        case 6: if(dayInt > 30) // june does not have more than 30 days
                    return false;
                break;

        case 9: if(dayInt > 30) // september does not have more than 30 days
                    return false;
                break;

        case 11:if(dayInt > 30) // november does not have more than 30 days
                    return false;
                break;
    }

    return true; // if all validations pass, returns true
}

bool Report::validateUptime(const char* uptime)
{
    if(uptime == NULL)
        return false;

    string uptimeString(uptime);

    int minuteInt, secondInt;
    size_t firstColonPosition, secondColonPosition, thirdColonCheck;
    string hourString, minuteString, secondString;

    // looks for the first ":" in the uptime string, then checks to see if it is found or not
    firstColonPosition = uptimeString.find(":");
    if(firstColonPosition == string::npos)
        return false;

    // if the first ":" is the first character in the string, this means there is no hour input
    if(firstColonPosition == 0)
        return false;

    // look for the second ":" in the uptime string, and checks to see if it is found or not
    secondColonPosition = uptimeString.find(":", firstColonPosition + 1);
    if(secondColonPosition == string::npos)
        return false;

    // checks to see if the first ":" and the second ":" are next to each other or not
    // if it is, that means that there is no minute input
    if(firstColonPosition + 1 == secondColonPosition)
        return false;

    // checks to see if there are any extra ":" in the uptime string
    thirdColonCheck = uptimeString.find(":", secondColonPosition + 1);
    if(thirdColonCheck != string::npos)
        return false;

    // the second ":" should not be the last character in the string
    // this would mean that there is no second input
    if(secondColonPosition == (uptimeString.length() - 1))
        return false;

    // extracts the hour input from the uptime string
    hourString = uptimeString.substr(0, firstColonPosition);

    // checks if the hour input is a string that contains digits only
    if(isDigitString(hourString) == false)
        return false;

    // extracts the minute input from the uptime string
    minuteString = uptimeString.substr(firstColonPosition + 1, (secondColonPosition - (firstColonPosition + 1)));

    // checks if the minute input is a string that contains digits only
    if(isDigitString(minuteString) == false)
        return false;

    // converts the minute string into an integer variable
    minuteInt = atoi(minuteString.c_str());

    // minutes cannot be more than 59
    if(minuteInt > 59)
        return false;

    // extracts the second input from the uptime string
    secondString = uptimeString.substr(secondColonPosition + 1);

    // checks if the second input is a string that contains digits only
    if(isDigitString(secondString) == false)
        return false;

    // converts the second string into an integer variable
    secondInt = atoi(secondString.c_str());

    // seconds cannot be more than 59
    if(secondInt > 59)
        return false;

    return true; // returns true if all validations pass
}

bool Report::validateXMLContent()
{
    if(doc.RootElement() == NULL)
        return false;

    const XMLElement* arm = doc.FirstChildElement(); // sets the first root element
    const XMLElement* timestamp = NULL;
    const XMLElement* processed = NULL;
    const XMLElement* uptime = NULL;
    const XMLElement* errors = NULL;
    const XMLElement* error = NULL;
    const XMLElement* elementValidate = NULL;

    int attributeCount = 0;

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
    attributeCount = 0;
    for(const XMLAttribute* attribute = arm->FirstAttribute(); attribute; attribute = attribute->Next())
        attributeCount++;

    // there cannot be more than 1 attribute in the root element "arm"
    if(attributeCount > 1)
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
            attributeCount = 0;
            for(const XMLAttribute* attribute = timestamp->FirstAttribute(); attribute; attribute = attribute->Next())
                attributeCount++;

            // there cannot be more than 1 attribute in the element "timestamp"
            if(attributeCount > 1)
                return false;

            // validates the value in the attribute "date"
            if(validateDate(timestamp->Attribute("date")) == false)
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
            attributeCount = 0;
            for(const XMLAttribute* attribute = processed->FirstAttribute(); attribute; attribute = attribute->Next())
                attributeCount++;

            // there cannot be more than 1 attribute in the element "processed"
            if(attributeCount > 1)
                return false;

            // sets the value of the attribute "value" into a string
            string processedValueString(processed->Attribute("value"));

            // the value in the attribute "value" cannot be empty
            if(processedValueString.empty())
                return false;

            // checks to see if the value are digits only
            if(isDigitString(processedValueString) == false)
                return false;

            // checks if there are any elements in the element "processed"
            elementValidate = processed->FirstChildElement();
            if(elementValidate != NULL) // there should not be any elements inside the element "processed"
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
            attributeCount = 0;
            for(const XMLAttribute* attribute = uptime->FirstAttribute(); attribute; attribute = attribute->Next())
                attributeCount++;

            // there cannot be more than 1 attribute in the element "uptime"
            if(attributeCount > 1)
                return false;

            // validates the value of the attribute "value" from the element "uptime"
            if(validateUptime(uptime->Attribute("value")) == false)
                return false;

            // the element "uptime" should not have any elements inside it
            elementValidate = uptime->FirstChildElement();
            if(elementValidate != NULL)
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
            attributeCount = 0;
            for(const XMLAttribute* attribute = errors->FirstAttribute(); attribute; attribute = attribute->Next())
                attributeCount++;

            // there cannot be more than 1 attribute in the element "errors"
            if(attributeCount > 1)
                return false;

            // convert the attribute value into a string
            string errorCountString(errors->Attribute("count"));

            // value of attribute "count" cannot be empty
            if(errorCountString.empty())
                return false;

            // checks to see if the value of attribute "count" contains only digits
            if(isDigitString(errorCountString) == false)
                return false;

            // converts the "count" value into an integer
            int errorCountInt = atoi(errorCountString.c_str());

            // gets the first child element from the "errors" element
            error = errors->FirstChildElement();

            // if there are no error counts but there is an element in the element "errors"
            if(errorCountInt == 0 && error != NULL)
                return false;

            // iterates through each error in the element "errors"
            for(int i = 0; i < errorCountInt; i++)
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
                attributeCount = 0;
                for(const XMLAttribute* attribute = error->FirstAttribute(); attribute; attribute = attribute->Next())
                    attributeCount++;

                // there cannot be more than 0 attribute in the element "error"
                if(attributeCount > 0)
                    return false;

                // element "error" cannot have any child element
                elementValidate = error->FirstChildElement();
                if(elementValidate != NULL)
                    return false;

                error = error->NextSiblingElement();
            }

            // checks to see if there are any more sibling elements after errors
            elementValidate = errors->NextSiblingElement();
            if(elementValidate != NULL) // element "errors" should be the last element
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

// saveXMLFile() saves the current XMLDocument into the file XML_STORAGE_FILENAME
// returns false if user has not ran LoadXMLFile() before or it encountered an error saving the file
bool Report::saveXMLFile(QString fileName)
{
    string XML_STORAGE_FILENAME = fileName.toLocal8Bit().constData();

    if(doc.RootElement() == NULL)
        return false;

    if(doc.SaveFile(XML_STORAGE_FILENAME.c_str()) != 0)
        return false;

    return true;
}

//loadXMLFile() loads the file XML_STORAGE_FILENAME and validates the content
// returns false if it encounters any error loading the file or the content does not pass validation test
bool Report::loadXMLFile(const char* XML_STORAGE_FILENAME)
{
    if(doc.LoadFile(XML_STORAGE_FILENAME) != 0)
    {
        ofstream outfile;
        outfile.open(XML_STORAGE_FILENAME);
        outfile << "<arm id=\"4321\"/>" << endl;
        outfile.close();

        if(doc.LoadFile(XML_STORAGE_FILENAME) != 0)
         return false;
    }

    if(validateXMLContent() == false)
        return false;

    return true;
}

// displaySpecificTimestamp() takes in a date format and displays the timestamps data
// returns false if LoadXMLFile() has not been used or if date format is not valid
bool Report::displaySpecificTimestamp(QString qDate)
{
    string date = qDate.toLocal8Bit().constData();

    if(doc.RootElement() == NULL)
        return false;

    if(validateDate(date.c_str()) == false)
        return false;

    XMLElement* timestamp = doc.FirstChildElement()->FirstChildElement();
    XMLElement* processed = NULL;
    XMLElement* uptime = NULL;
    XMLElement* errors = NULL;

    while(timestamp != NULL) // iterates through the whole timestamp record
    {
        if(strcmp(timestamp->Attribute("date"), date.c_str()) == 0) // if the date matches the timestamp
        {
            processed = timestamp->FirstChildElement("processed");
            uptime = processed->NextSiblingElement("uptime");
            errors = uptime->NextSiblingElement("errors");

            // converts char* into QString
            QString processedQString = QString::fromUtf8(processed->Attribute("value"));
            QString uptimeQString = QString::fromUtf8(uptime->Attribute("value"));
            QString countQString = QString::fromUtf8(errors->Attribute("count"));

            emit sendTimestampData(processedQString, uptimeQString, countQString);
            return true;
        }

        timestamp = timestamp->NextSiblingElement();
    }

    emit sendTimestampData("nil", "nil", "nil"); // when there are no records found

    return true;
}

// generateMasterReport() takes in a filename of a excel template file and generates a master report file from it
// returns true if successful, false if failed
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
                int errorCountInt = errors->IntAttribute("count");
                error = errors->FirstChildElement("error");
                if(errorCountInt == 0) // if there are no errors from the date
                {
                    data->SetAttribute("ss:Type", "String");
                    data->SetText("Nil");
                    cell->InsertEndChild(data);
                    row->InsertEndChild(cell);
                    table->InsertEndChild(row);
                }
                else // at least one error was found in the date
                {
                    for(int j = 0; j < errorCountInt; j++) // iterates through each errors
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
    masterFileStream.open(MASTER_REPORT_FILENAME);
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

    remove("MasterReport.temp");

    return true;
}

// updateTimestamp() takes in a date, uptime, and cycleCount and add a new timestamp, if it exist, it updates the data
// returns true if successful, false if it fails
bool Report::updateTimestamp(QString qDate, int uptimeInt, int processedValueInt)
{
    string dateString = qDate.toLocal8Bit().constData();
    stringstream ss;

    if(doc.RootElement() == NULL)
        return false;

    if(Report::isTimestampExist(dateString) == false) // if the timestamp doesn't exist, it will create a new one
    {
        XMLElement* arm = doc.FirstChildElement();
        XMLElement* timestamp = doc.NewElement("timestamp");
        XMLElement* processed = doc.NewElement("processed");
        XMLElement* uptime = doc.NewElement("uptime");
        XMLElement* errors = doc.NewElement("errors");

        int totalSeconds = uptimeInt / 1000; // uptimeInt is in millisecond, converts to second
        int hours = totalSeconds / 3600;
        int minutes = (totalSeconds / 60) - (hours * 60);
        int seconds = totalSeconds % 60;
        ss.str("");
        ss << hours << ":" << minutes << ":" << seconds;

        // sets the attribute of the elements
        timestamp->SetAttribute("date", dateString.c_str());
        processed->SetAttribute("value", processedValueInt);
        uptime->SetAttribute("value", ss.str().c_str());
        errors->SetAttribute("count", 0);

        // adds into the timestamp element and then the root "arm" element
        timestamp->InsertEndChild(processed);
        timestamp->InsertEndChild(uptime);
        timestamp->InsertEndChild(errors);
        arm->InsertEndChild(timestamp);
    }
    else // if the timestamp already exist in the record, take the existing data and update it
    {
        XMLElement* timestamp = doc.FirstChildElement()->FirstChildElement();
        XMLElement* processed = NULL;
        XMLElement* uptime = NULL;

        while(timestamp != NULL) // iterates through the whole timestamp record
        {
            if(strcmp(timestamp->Attribute("date"), dateString.c_str()) == 0) // if the date matches the timestamp
            {
                processed = timestamp->FirstChildElement("processed");
                uptime = processed->NextSiblingElement("uptime");

                // updates the cycleCount value for the date
                int retrievedProcessed = processed->IntAttribute("processed");
                processed->SetAttribute("value", (retrievedProcessed + processedValueInt));

                // tokenizes the date string into seperate string values such as hours, minutes, seconds
                string retrievedUptime(uptime->Attribute("value"));
                string retrievedHours = retrievedUptime.substr(0, retrievedUptime.find(':') + 1);
                string retrievedMinuteAndSecond = retrievedUptime.substr(retrievedUptime.find(':') + 1);
                string retrievedMinute = retrievedMinuteAndSecond.substr(0, retrievedMinuteAndSecond.find(':') + 1);
                string retrievedSecond = retrievedMinuteAndSecond.substr(retrievedMinuteAndSecond.find(':') + 1);

                // converts from hours in string to int
                ss.str(""); ss << retrievedHours;
                int retrievedHoursInt;
                ss >> retrievedHoursInt;

                // converts from minutes in string to int
                ss.str(""); ss << retrievedMinute;
                int retrievedMinuteInt;
                ss >> retrievedMinuteInt;

                // converts from seconds in string to int
                ss.str(""); ss << retrievedSecond;
                int retrievedSecondInt;
                ss >> retrievedSecondInt;

                // calculate the total seconds and updates the one from the parameter uptime
                int totalSecond = (retrievedHoursInt * 60 * 60) + (retrievedMinuteInt * 60) + retrievedSecondInt;
                totalSecond = totalSecond + (uptimeInt / 1000);

                // converts back the total seconds into the human readable format
                int hours = totalSecond / 3600;
                int minutes = (totalSecond / 60) - (hours * 60);
                int seconds = totalSecond % 60;
                stringstream newSS;
                newSS << hours << ":" << minutes << ":" << seconds;
                uptime->SetAttribute("value", newSS.str().c_str()); // updates the element attribute

                return true;
            }

            timestamp = timestamp->NextSiblingElement();
        }
    }

    return true;
}

// isTimestampExist takes in a date string and checks if the date record exists or not
// return false if not found, else it will return true
bool Report::isTimestampExist(const string& date)
{
    if(doc.RootElement() == NULL)
        return false;

    if(validateDate(date.c_str()) == false) // validates the parameter date
        return false;

    XMLElement* timestamp = doc.FirstChildElement()->FirstChildElement(); // gets the first timestamp element

    while(timestamp != NULL) // iterates through the whole timestamp record
    {
        if(strcmp(timestamp->Attribute("date"), date.c_str()) == 0) // if the date matches the timestamp
        {
            return true;
        }

        timestamp = timestamp->NextSiblingElement();
    }

    return false;
}
