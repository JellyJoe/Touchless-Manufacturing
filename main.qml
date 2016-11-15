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
