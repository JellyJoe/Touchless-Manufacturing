import QtQuick 2.5
import QtQuick 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls 1.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.2
import QtQuick.Layouts 1.2
import QtQuick.Controls.Material 2.0
import QtQuick.Dialogs 1.2

Item {
    id: item1
    width: 1280
    height: 720

    /* Report button and background configuration */
    property alias btnDateReport: btnDateReport
    property alias btnMasterReport: btnMasterReport
    property alias calendar: calendar
    property alias masterReportBackground:masterReportBackground
    property alias dateReportBackground:dateReportBackground

    transformOrigin: Item.Center


    Rectangle {
        id: rectangle1
        color: "#232323"
        anchors.fill: parent
        clip: false
        border.color: "#232323"



        Calendar {
            id: calendar

            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.leftMargin: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 138
            anchors.top: txtReportTitle.bottom
            anchors.topMargin: 15
            anchors.left: parent.left



        }



        Button {
            id: btnMasterReport
            x: 498
            y: 655
            width: 314
            height: 40
            checkable: true
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter

            background: Rectangle {
                id:masterReportBackground
                color: "#2bb9ef"
                radius: 15
                border.width: 1

                Label{
                    x: 66
                    y: 8
                    text: qsTr("Generate Master Report")
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 15
                    color: "#000000"
                    anchors.centerIn: parent
                }

            }

        }

        Button {
            id: btnDateReport
            x: 476
            y: 600
            width: 314
            height: 40
            anchors.horizontalCenterOffset: 0
            spacing: 0
            topPadding: 6
            anchors.horizontalCenter: parent.horizontalCenter
            checkable: true

            background: Rectangle {
                id:dateReportBackground
                color: "#2bb9ef"
                radius: 15
                border.width: 1

                Label{
                    x: 66
                    y: 8
                    text: qsTr("Selected Date Report")
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 15
                    color: "#000000"
                    anchors.centerIn: parent
                }

            }

        }

        Text {
            id: txtReportTitle
            x: 247
            y: 17
            width: 487
            height: 53
            color: "#4ecbfb"
            text: qsTr("Performance Report")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 650
            verticalAlignment: Text.AlignVCenter
            font.family: "Tahoma"
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 30
        }


    }


}




