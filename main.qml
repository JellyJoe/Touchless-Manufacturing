import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2

ApplicationWindow
{
    visible: true
    visibility: Window.FullScreen
    width: 640
    height: 480
    title: qsTr("Touchless Manufacturing")

    property string xml_data_storage_filename: "C:\\Users\\Joe\\Documents\\Touchless-Manufacturing\\Arm_Data_Storage.xml"
    //property string xml_data_storage_filename: "C:\\Users\\Sukhdip\\Documents\\TouchlessManufacturingApplication\\Arm_Data_Storage.xml"

    property int cycleCount
    property int elapsedTime
    property string date

    SwipeView
    {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex


        Report
        {

        }

        CtrlPanel
        {

        }
    }

    header: TabBar
    {
        id: tabBar
        currentIndex: swipeView.currentIndex



        TabButton
        {
            id:btnReportView
            text: qsTr("Report View")
        }

        TabButton
        {
            id:btnControlPanel
            text: qsTr("Control Panel")

        }

        TabButton
        {
            id: btnExit
            text: qsTr("Exit")

            MessageDialog
            {
                id: dialogExit
                title: "Close Program"
                icon: StandardIcon.Warning

                standardButtons: StandardButton.Ok | StandardButton.Cancel
                text: "Exit Touchless Manufacturing Application?"
                onAccepted:
                {
                    //get the cycle count from Arm class
                    cycleCount = _myArm.getCycle()
                    //get elapsed time in milliseconds from Arm class
                    elapsedTime = _myArm.getElapsedTime()
                    //get current date
                    date = Qt.formatDateTime(new Date(), "dd-MM-yyyy")

                    //call report function to update process details
                    _report.updateTimestamp(date, elapsedTime, cycleCount)

                    //debug value
                    console.debug(" ", cycleCount, " ", elapsedTime, " ", date)

                    // saves the loaded xml file
                    _report.saveXMLFile(xml_data_storage_filename)


                    //delete the arm instance to disconnect and stop arm
                    delete _myArm

                    Qt.quit()
                }

                onRejected:
                {

                    tabBar.currentIndex = 0

                }
            }
            onClicked: dialogExit.visible = true
        }
    }
}
