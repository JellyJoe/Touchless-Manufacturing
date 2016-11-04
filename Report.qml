import QtQuick 2.5
import QtQuick 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls 1.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.2
import QtQuick.Layouts 1.2
import QtQuick.Controls.Material 2.0
import QtQuick.Dialogs 1.2


ReportForm {

    //Master Report Prompt Dialog
    MessageDialog{

            id: msgMasterReport
            title: "Master Report"

            property string txtMasterPrompt: "The MasterReport.xml file has been created"

            text: txtMasterPrompt
            icon: StandardIcon.Information
            onAccepted: visible = false
        }

    //Chosen Date Report Dialog
    MessageDialog {

            id: msgReport
            title: "Selected Date Report"

            property string date: Qt.formatDateTime(calendar.selectedDate, "dd-MM-yyyy")
            property int count: 10
            property int uptime: 200
            property int error: 5

            text: "Date: " + date + "\nProcess Count: " + count + "\nUptime: " + uptime + "\nError: " + error

            icon: StandardIcon.Information
            onAccepted: visible = false
        }


    btnMasterReport.onClicked: msgMasterReport.visible = true



    //Date Report Button onclick
    btnDateReport.onClicked: msgReport.visible = true

}


