import QtQuick 2.5
import QtQuick 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls 1.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.2
import QtQuick.Layouts 1.2
import QtQuick.Controls.Material 2.0
import QtQuick.Dialogs 1.2

ReportForm
{
    //===================================================================================
    //                              MASTER REPORT

    property string excel_template_filename: "C:\\Users\\Sukhdip\\Documents\\TouchlessManufacturingApplication\\Excel_Template.xml"

    //Master report button onclick
    btnMasterReport.onClicked:
    {
        _myReport.generateMasterReport(excel_template_filename)
        msgMasterReport.visible = true
    }

    //lighter colour onclick
    btnMasterReport.onPressed:
    {
        masterReportBackground.color = "#68ccf2"
    }

    //original colour upon release
    btnMasterReport.onReleased:
    {
        masterReportBackground.color = "#2bb9ef"
    }

    //Master Report Prompt Dialog
    MessageDialog
    {
        id: msgMasterReport
        title: "Master Report"

        property string txtMasterPrompt: "The MasterReport file has been created on the desktop."

        text: txtMasterPrompt
        icon: StandardIcon.Information
        onAccepted: visible = false
    }

    //===================================================================================
    //                              SPECIFIC DATE REPORT

    //date selection based on calendar click
    property string date: Qt.formatDateTime(calendar.selectedDate, "dd-MM-yyyy")


    //establish connection for the data retrieval from the xml
    Connections
    {
        target: _myReport
        onSendTimestampData:
        {
            if(processed === "nil")
            {
                msgReport.text = "No records found for " + date
            }
            else
            {
                msgReport.text = "Date: " + date + "\nProcess Count: " + processed + "\nUptime: " + uptime + "\nError: " + errorCount
            }
            msgReport.visible = true
        }
    }

    //Date Report Button onclick
    btnDateReport.onClicked: _myReport.displaySpecificTimestamp(date)

    //lighter colour onclick
    btnDateReport.onPressed:
    {
        dateReportBackground.color = "#68ccf2"
    }

    //original colour upon release
    btnDateReport.onReleased:
    {
        dateReportBackground.color = "#2bb9ef"
    }

    //Chosen Date Report Dialog
    MessageDialog
    {

        id: msgReport
        title: "Selected Date Report"
        icon: StandardIcon.Information
        onAccepted: visible = false
        standardButtons: StandardButton.Ok


    }
}
