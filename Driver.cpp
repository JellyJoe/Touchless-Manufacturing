#include <iostream>
#include <string>
#include <fstream>
#include "Report.h"

using namespace std;
using namespace tinyxml2;

// <?mso-application progid="Excel.Sheet"?>

const char XML_STORAGE_FILENAME[] = "Arm_Data_Storage.xml";
const char EXCEL_TEMPLATE_FILENAME[] = "Excel_Template.xml";

bool GenerateMasterReport()
{
    XMLDocument doc;
    doc.LoadFile(XML_STORAGE_FILENAME);

    XMLDocument excelDoc;
    excelDoc.LoadFile(EXCEL_TEMPLATE_FILENAME);

    if(excelDoc.ErrorID() != 0)
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


    for(int i = 0; i < 2; i++)
    {
        XMLElement* row = excelDoc.NewElement("Row");
        XMLElement* cell = excelDoc.NewElement("Cell");
        XMLElement* data = excelDoc.NewElement("Data");

        if(i == 0)
        {
            // Arm Merge First Row
            cell->SetAttribute("ss:MergeAcross", 3);
            cell->SetAttribute("ss:StyleID", "s63");
            data->SetAttribute("ss:Type", "String");
            data->SetText("Arm");

            cell->InsertEndChild(data);
            row->InsertEndChild(cell);
            table->InsertEndChild(row);
        }
        else if(i == 1)
        {
            for(int j = 0; j < 4; j++)
            {
                cell = excelDoc.NewElement("Cell");
                data = excelDoc.NewElement("Data");
                data->SetAttribute("ss:Type", "String");

                if(j == 0)
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

    XMLElement* arm = doc.FirstChildElement();
    const XMLElement* timestamp = arm->FirstChildElement("timestamp");
    const XMLElement* processed = NULL;
    const XMLElement* uptime = NULL;
    const XMLElement* errors = NULL;
    const XMLElement* error = NULL;

    if(timestamp ==  NULL) // no records
        return false;

    while(timestamp != NULL)
    {
        XMLElement* row = excelDoc.NewElement("Row");
        XMLElement* cell = excelDoc.NewElement("Cell");
        XMLElement* data = excelDoc.NewElement("Data");

        processed = timestamp->FirstChildElement("processed");
        uptime = processed->NextSiblingElement("uptime");
        errors = uptime->NextSiblingElement("errors");
        error = NULL;

        for(int i = 0; i < 4; i++)
        {
            cell = excelDoc.NewElement("Cell");
            data = excelDoc.NewElement("Data");

            if(i == 0)
            {
                data->SetText(timestamp->Attribute("date"));
                data->SetAttribute("ss:Type", "String");
                cell->InsertEndChild(data);
                row->InsertEndChild(cell);
            }
            else if(i == 1)
            {
                data->SetText(processed->Attribute("value"));
                data->SetAttribute("ss:Type", "Number");
                cell->InsertEndChild(data);
                row->InsertEndChild(cell);
            }
            else if(i == 2)
            {
                data->SetText(uptime->Attribute("value"));
                data->SetAttribute("ss:Type", "String");
                cell->InsertEndChild(data);
                row->InsertEndChild(cell);
            }
            else
            {
                int error_count_int = errors->IntAttribute("count");
                error = errors->FirstChildElement("error");
                if(error_count_int == 0)
                {
                    data->SetAttribute("ss:Type", "String");
                    data->SetText("Nil");
                    cell->InsertEndChild(data);
                    row->InsertEndChild(cell);
                    table->InsertEndChild(row);
                }
                else
                {
                    for(int j = 0; j < error_count_int; j++)
                    {
                        if(j == 0)
                        {
                            data->SetAttribute("ss:Type", "String");
                            data->SetText(error->GetText());
                            cell->InsertEndChild(data);
                            row->InsertEndChild(cell);
                            table->InsertEndChild(row);
                        }
                        else
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

        timestamp = timestamp->NextSiblingElement("timestamp");
    }

    if(excelDoc.SaveFile("MasterReport.temp") != 0)
        return false;

    string temp;
    ofstream masterFileStream;
    masterFileStream.open("MasterReport.xml");
    if(!masterFileStream) // file not found or cannot be opened
        return false;

    ifstream tempFileStream;
    tempFileStream.open("MasterReport.temp");
    if(!tempFileStream)
        return false;

    masterFileStream << "<?xml version=\"1.0\"?>" << endl;
    masterFileStream << "<?mso-application progid=\"Excel.Sheet\"?>" << endl;

    getline(tempFileStream, temp); // removes the first line from the master temp file
    while(!tempFileStream.eof())
    {
        getline(tempFileStream, temp);
        masterFileStream << temp << endl;
    }

    masterFileStream.close();
    tempFileStream.close();

    return true;
}

int main()
{
    if(Report::LoadXMLFile(XML_STORAGE_FILENAME) == false)
    {
        cout << "Failed to load / validate \"" << XML_STORAGE_FILENAME << "\"." << endl;
        return -1;
    }
    else
        cout << "\"" << XML_STORAGE_FILENAME << "\" loaded and validated." << endl;

    string choice, date;

    do {
        cout << endl << "Report Menu" << endl;
        cout << "-----------" << endl;
        cout << "1. Add Timestamp" << endl;
        cout << "2. Display Specific Timestamp" << endl;
        cout << "3. Display All Timestamp" << endl;
        cout << "4. Remove Timestamp" << endl;
        cout << "5. Generate Master Report" << endl;
        cout << "6. Exit" << endl;
        cout << endl << "Enter choice: ";
        getline(cin, choice);
            while(choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "6")
            {
                cout << "Invalid choice! Re-enter: ";
                getline(cin, choice);
            }

        cout << endl;
        if(choice == "1")
        {
            cout << "This function will be adjusted according to the data obtained from the arm." << endl;
            cout << "For now, it will be adding fixed data." << endl;
            if(Report::AddTimestamp() == true)
                cout << "New timestamp has been added." << endl;
            else
                cout << "Use Report::LoadXMLFile() to load the XML document first." << endl;
        }
        else if(choice == "2")
        {
            cout << "Enter date to search (try 11-5-2016): ";
            getline(cin, date);
                while(Report::ValidateDate(date.c_str()) == false)
                {
                    cout << "Invalid date! Re-enter: ";
                    getline(cin, date);
                }

            cout << endl;
            if(Report::DisplaySpecificTimestamp(date) == false)
                cout << "Use Report::LoadXMLFile() to load the XML document first." << endl;
        }
        else if(choice == "3")
        {
            if(Report::DisplayAllTimestamp() == false)
                cout << "Use Report::LoadXMLFile() to load the XML document first." << endl;
        }
        else if(choice == "4")
        {
            cout << "Enter date to delete (try 11-5-2016): ";
            getline(cin, date);
                while(Report::ValidateDate(date.c_str()) == false)
                {
                    cout << "Invalid date! Re-enter: ";
                    getline(cin, date);
                }

            cout << endl;
            if(Report::DeleteTimestamp(date) == false)
                cout << "Use Report::LoadXMLFile() to load the XML document first." << endl;
        }
        else if(choice == "5")
        {
            GenerateMasterReport();
        }
        else
            cout << "Thanks for trying this out!" << endl;

    } while(choice != "6");

    return 0;
}
