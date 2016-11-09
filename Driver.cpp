#include <iostream>
#include <string>
#include "Report.h"

using namespace std;
using namespace tinyxml2;

const char XML_STORAGE_FILENAME[] = "Arm_Data_Storage.xml";

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
        cout << "5. Exit" << endl;
        cout << endl << "Enter choice: ";
        getline(cin, choice);
            while(choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5")
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
        else
            cout << "Thanks for trying this out!" << endl;

    } while(choice != "5");

    return 0;
}
