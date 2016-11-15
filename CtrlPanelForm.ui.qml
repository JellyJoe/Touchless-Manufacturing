import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.2

Item {

    id: item3
    width: 1280
    height: 720
    property alias txtManualMoveRecord: txtManualMoveRecord

    //=======================================================================================================
    //                          Property declarations for button and background


    //Automatic process configuration (button and background)
    property alias btnConnectAuto: btnConnectAuto //establish connection with the arm
    property alias btnActivateArmAuto: btnActivateArmAuto //execute arms based on auto config
    property alias btnStopArmAuto: btnStopArmAuto //stop arm process
    property alias btnSignatureFetch: btnSignatureFetch //open up pixymon for signature store into pixy
    property alias btnStamperPosition: btnStamperPosition //get the stamper position
    property alias btnPositionEnd: btnPositionEnd //get the end placement position

    property alias positionEndBackground: positionEndBackground //btnPositionEnd background
    property alias stamperBackground: stamperBackground //btnStamperPosition background
    property alias signatureBackground: signatureBackground //btnSignatureFetch background
    property alias connectManualBackground:connectManualBackground //btnConnectManual background




    //Manual process configuration (button and background)
    property alias btnConnectManual: btnConnectManual //establish connection with arm
    property alias btnActivateArmManual: btnActivateArmManual //execute arm based on manual config
    property alias btnStopArmManual: btnStopArmManual //stop arm process
    property alias btnMoveWithPump: btnMoveWithPump // store coordinate with pump
    property alias btnMoveWithoutPump: btnMoveWithoutPump //store coordinate without pump

    property alias withPumpBackground: withPumpBackground //btnMoveWithPump background
    property alias withoutPumpBackground: withoutPumpBackground //btnMoveWithoutPump background
    property alias connectAutoBackground:connectAutoBackground //btnConnectAuto background


    //Demo process configuration (button)
    property alias btnDemo: btnDemo

    //=======================================================================================================


    //position the item container to center
    transformOrigin: Item.Center


    Rectangle {
        id: rectangle1
        color: "#232323"
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        clip: false
        border.color: "#232323"

        ColumnLayout {
            x: 24
            width: 1079
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 8
            anchors.top: txtReportTitle.bottom
            anchors.bottom: parent.bottom
            anchors.topMargin: 12
            spacing: 0

            GroupBox {
                id: boxManualConfig
                width: 933

                spacing: 20
                title: qsTr("Manual Configuration")
                label: Text {
                     color: "white"
                     font.pointSize: 15
                     text: boxManualConfig.title
                     font.bold: true
                  }
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredHeight: 288
                Layout.preferredWidth: 929
                topPadding: 20

                contentData: [

                Button {
                    id: btnConnectManual
                    x: 66
                    y: 194
                    width: 100
                    height: 47
                    text: qsTr("Connect Arm")
                    enabled: true

                    background: Rectangle {
                        id: connectManualBackground
                        color: "#E0E0E0"
                    }
                },

                Button {
                    id: btnActivateArmManual
                    x: 207
                    y: 195
                    width: 100
                    height: 47
                    text: qsTr("Activate Arm")
                    enabled: false
                    },

                Button {
                    id: btnStopArmManual
                    x: 350
                    y: 194
                    width: 100
                    height: 47
                    text: qsTr("Stop Arm")
                    enabled: false
                    checkable: false
                    },

                Button {
                    id: btnMoveWithPump
                    x: 66
                    y: 116
                    width: 154
                    height: 46
                    text: "Set move with pump"
                    enabled: false
                    autoRepeat: false
                    autoExclusive: false
                    background: Rectangle {
                        id: withPumpBackground
                        color: "#2bb9ef"
                        radius: 20
                        border.width: 2
                    }
                },

                Button {
                    id: btnMoveWithoutPump
                    x: 66
                    y: 43
                    width: 154
                    height: 46
                    text: "Set move without pump"
                    enabled: false
                    background: Rectangle {
                        id:withoutPumpBackground
                        color: "#2bb9ef"
                        radius: 20
                        border.width: 2

                    }
                },

                TextArea {
                    id: txtManualMoveRecord
                    x: 464
                    y: 6
                    width: 465
                    height: 236
                    anchors.right: parent.right
                    anchors.rightMargin: 20

                    background: Rectangle{
                        color:"white"
                    }
                },

                Text {
                        id: text10
                        x: 246
                        y: 45
                        width: 284
                        height: 42
                        color: "#ffffff"
                        text: "Click to save coordinate<br> without suction"
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignLeft
                        font.pixelSize: 19
                        styleColor: "#00000000"
                        wrapMode: Text.WordWrap
                    },

                    Text {
                        id: text11
                        x: 246
                        y: 118
                        width: 284
                        height: 42
                        color: "#ffffff"
                        text: "Click to save coordinate <br>with suction activated"
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: 19
                        styleColor: "#00000000"
                        horizontalAlignment: Text.AlignLeft
                        wrapMode: Text.WordWrap
                    }
                ]




            }

            RowLayout {
                Layout.fillHeight: false
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                spacing: 10

                GroupBox {
                    id: boxAutoConfig
                    Layout.fillWidth: true
                    Layout.preferredHeight: 273
                    Layout.preferredWidth: 455
                    z: 1
                    topPadding: 20
                    title: qsTr("Auto Configuration")
                    label: Text {
                         color: "white"
                         font.pointSize: 15
                         text: boxAutoConfig.title
                         font.bold: true
                    }
                    contentData: [

                        Button {
                            id: btnConnectAuto
                            x: 111
                            y: 190
                            width: 100
                            height: 47
                            text: qsTr("Connect Arm")
                            anchors.horizontalCenterOffset: -139
                            anchors.horizontalCenter: parent.horizontalCenter
                            enabled: true

                            background: Rectangle {
                                id: connectAutoBackground
                                color: "#E0E0E0"
                            }
                        },

                        Button {
                            id: btnActivateArmAuto
                            x: 111
                            y: 190
                            width: 100
                            height: 47
                            text: qsTr("Activate Arm")
                            anchors.horizontalCenterOffset: 1
                            anchors.horizontalCenter: parent.horizontalCenter
                            enabled: false
                        },

                        Button {
                            id: btnStopArmAuto
                            x: 111
                            y: 190
                            width: 100
                            height: 47
                            text: qsTr("Stop Arm")
                            anchors.horizontalCenterOffset: 141
                            anchors.horizontalCenter: parent.horizontalCenter
                            enabled: false
                        },

                        Button {
                            id: btnSignatureFetch
                            x: 330
                            y: 20
                            width: 113
                            height: 38
                            text: "Set"
                            enabled: false

                            hoverEnabled: true;

                            background: Rectangle {
                                id:signatureBackground
                                color: "#2bb9ef"
                                radius: 20
                                border.width: 2

                            }

                        },
                        Text {
                            id: txtSignatureFetch
                            x: 49
                            y: 23
                            color: "#ffffff"
                            text: "Fetch Item Signature"
                            wrapMode: Text.WordWrap
                            font.pixelSize: 25
                            styleColor: "#00000000"
                        },

                        Button {
                            id: btnStamperPosition
                            x: 330
                            y: 74
                            width: 113
                            height: 38
                            text: "Set"
                            enabled: false
                            background: Rectangle {
                                id:stamperBackground
                                color: "#2bb9ef"
                                radius: 20
                                border.width: 2
                            }



                        },
                        Text {
                            id: txtStamperPosition
                            x: 49
                            y: 77
                            color: "#ffffff"
                            text: "Set Stamper Position"
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.WordWrap
                            font.pixelSize: 25
                            styleColor: "#00000000"
                        },
                        Button {
                            id: btnPositionEnd
                            x: 330
                            y: 127
                            width: 113
                            height: 38
                            text: "Set"
                            enabled: false
                            background: Rectangle {
                                id:positionEndBackground
                                color: "#2bb9ef"
                                radius: 20
                                border.width: 2
                            }
                        },
                        Text {
                            id: txtPositionEnd
                            x: 49
                            y: 127
                            color: "#ffffff"
                            text: "Set End Position"
                            wrapMode: Text.WordWrap
                            font.pixelSize: 25
                            styleColor: "#00000000"
                        }
                    ]
                }

                GroupBox {
                    id: boxTroubleshoot
                    Layout.fillWidth: true
                    Layout.preferredHeight: 273
                    Layout.preferredWidth: 468
                    topPadding: 20
                    title: qsTr("Troubleshoot Demo")
                    label: Text {
                         color: "white"
                         font.pointSize: 15
                         text: boxTroubleshoot.title
                         font.bold: true
                      }
                    contentData: [

                        Button {
                            id: btnDemo
                            x: 137
                            y: 188
                            width: 197
                            height: 47
                            text: qsTr("Arm Demo")
                            anchors.horizontalCenterOffset: 1
                            anchors.horizontalCenter: parent.horizontalCenter

                        },
                        Text {
                            id: txtDemoDescription
                            x: 0
                            y: 8
                            width: 438
                            height: 161
                            color: "#ffffff"
                            text: "In order to check for any movement fault, we recommend that you execute the demo. This will test the movement based on preset coordinates and vacuum function."
                            anchors.horizontalCenter: parent.horizontalCenter
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            font.pixelSize: 25
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                            styleColor: "#00000000"
                        }]
                }
            }
        }


        Text {
            id: txtReportTitle
            x: 247
            y: 29
            width: 487
            height: 53
            color: "#4ecbfb"
            text: qsTr("Control Panel")
            anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 30
            font.family: "Tahoma"
            font.bold: true
        }

    }
}
