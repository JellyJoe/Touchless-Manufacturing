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
    property string date: Qt.formatDateTime(calendar.selectedDate, "dd-MM-yyyy")

    Connections
    {
        target: _report
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

    //Master report button onclick
    btnMasterReport.onClicked: msgMasterReport.visible = true

    //Master Report Prompt Dialog
    MessageDialog
    {
        id: msgMasterReport
        title: "Master Report"

        property string txtMasterPrompt: "The MasterReport.xml file has been created"

        text: txtMasterPrompt
        icon: StandardIcon.Information
        onAccepted: visible = false
    }

    //Date Report Button onclick
    btnDateReport.onClicked: _report.displaySpecificTimestamp(date)

    //Chosen Date Report Dialog
    MessageDialog
    {
        id: msgReport
        title: "Selected Date Report"
        icon: StandardIcon.Information
        onAccepted: visible = false
    }
}
