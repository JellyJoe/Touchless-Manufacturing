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

    //property string xml_data_storage_filename: "C:\\Users\\Joe\\Documents\\Touchless-Manufacturing\\Arm_Data_Storage.xml"
    property string xml_data_storage_filename: "C:\\Users\\Sukhdip\\Documents\\TouchlessManufacturingApplication\\Arm_Data_Storage.xml"

    //property declaration for report variables
    property int cycleCount
    property int elapsedTime
    property string date

    //swipe view to allow swipe navigation
    SwipeView
    {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex //work with tab bar to get index of page navigated to

        //report view
        Report
        {

        }

        //control panel view
        CtrlPanel
        {

        }
    }

    //tab header for menu selection
    header: TabBar
    {
        id: tabBar
        //work with swipe view to get index of page
        currentIndex: swipeView.currentIndex


        //report tab button
        TabButton
        {
            id:btnReportView
            text: qsTr("Report View")
        }

        //control panel tab button
        TabButton
        {
            id:btnControlPanel
            text: qsTr("Control Panel")

        }

        //exit button containing confirmation dialog for exit and variable saving into xml
        TabButton
        {
            id: btnExit
            text: qsTr("Exit")

            //confirmation dialog for exit
            MessageDialog
            {
                id: dialogExit
                title: "Close Program"
                icon: StandardIcon.Warning

                standardButtons: StandardButton.Ok | StandardButton.Cancel
                text: "Exit Touchless Manufacturing Application?"

                //on exit confirmation
                onAccepted:
                {
                    //get the cycle count from Arm class
                    cycleCount = _myArm.getCycle()
                    //get elapsed time in milliseconds from Arm class
                    elapsedTime = _myArm.getElapsedTime()
                    //get current date
                    date = Qt.formatDateTime(new Date(), "dd-MM-yyyy")

                    //call report function to update process details
                    _myReport.updateTimestamp(date, elapsedTime, cycleCount)

                    //debug value
                    console.debug(" ", cycleCount, " ", elapsedTime, " ", date)

                    // saves the loaded xml file
                    if(_myReport.saveXMLFile(xml_data_storage_filename) === true)
                        console.debug("Saved")
                    else
                        console.debug("Not saved")


                    //delete the arm instance to disconnect and stop arm
                    delete _myArm
                    delete _myPixy

                    Qt.quit()
                }

                //if exit cancelled navigate back to index 0
                onRejected:
                {

                    tabBar.currentIndex = 0

                }
            }

            //on clicking the tab exit button, the confirmation dialog for exit will be visible
            onClicked: dialogExit.visible = true
        }
    }
}
