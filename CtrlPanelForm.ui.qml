import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.2

Item {

    id: controlPanelItem
    width: 1280
    height: 720
    property alias btnHeightFetch: btnHeightFetch
    property alias btnPositionStart: btnPositionStart
    property alias txtExecutionDisplay: txtExecutionDisplay

    //=======================================================================================================
    //                          Property declarations for button and background


    //Automatic process configuration (button and background)
    property alias btnConnectAuto: btnConnectAuto //establish connection with the arm
    property alias btnActivateArmAuto: btnActivateArmAuto //execute arms based on auto config
    property alias btnStopArmAuto: btnStopArmAuto //stop arm process
    property alias btnSignatureFetch: btnSignatureFetch //open up pixymon for signature store into pixy
    property alias btnStamperPosition: btnStamperPosition //get the stamper position
    property alias btnPositionEnd: btnPositionEnd //get the end placement position

    property alias positionStartBackground: positionStartBackground //btnPositionStart background
    property alias stamperBackground: stamperBackground //btnStamperPosition background
    property alias positionEndBackground: positionEndBackground //btnPositionEnd background
    property alias signatureBackground: signatureBackground //btnSignatureFetch background
    property alias heightBackground: heightBackground //btnHeightFetch background
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
    property alias btnDemo: btnDemo //execute demo function
    property alias demoBackground: demoBackground //btnDemo background

    //=======================================================================================================


    //position the item container to center
    transformOrigin: Item.Center


    //outer encapsulation
    Rectangle {
        //rectangle formatting
        id: encapsulationRectangle
        color: "#232323"
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        clip: false
        border.color: "#232323"

        //alignment of panels using columns
        ColumnLayout {
            x: 24
            width: 1079
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 8
            anchors.top: txtControlTitle.bottom
            anchors.bottom: parent.bottom
            anchors.topMargin: 12
            spacing: 0

            //groupboxes for different functionalities
            //manual configuration and textarea for status update
            GroupBox {
                //stlying and formatting
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

                //groupbox content and formating
                contentData: [

                //manual connect button
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

                //manual activate button
                Button {
                    id: btnActivateArmManual
                    x: 207
                    y: 195
                    width: 100
                    height: 47
                    text: qsTr("Activate Arm")
                    enabled: false
                    },

                //manual stop button
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

                //manual arm move with pump button
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

                    //blue rounded button format
                    background: Rectangle {
                        id: withPumpBackground
                        color: "#2bb9ef"
                        radius: 20
                        border.width: 2
                    }
                },

                //manual arm without pump button
                Button {
                    id: btnMoveWithoutPump
                    x: 66
                    y: 43
                    width: 154
                    height: 46
                    text: "Set move without pump"
                    enabled: false

                    //blue rounded button format
                    background: Rectangle {
                        id:withoutPumpBackground
                        color: "#2bb9ef"
                        radius: 20
                        border.width: 2

                    }
                },

                    //flickable text area for status display
                    Flickable {
                        id: flickableManualMoveRecord
                        width: 465
                        height: 236
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 20
                        contentWidth: txtExecutionDisplay.width
                        contentHeight: txtExecutionDisplay.height

                        TextArea.flickable: TextArea {
                            id: txtExecutionDisplay
                            width: 465
                            height: 236

                            background: Rectangle{
                                color:"black"
                                radius: 10
                            }

                        }

                    },

                    //save with without pump text description
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
                        font.pixelSize: 20
                        styleColor: "#00000000"
                        wrapMode: Text.WordWrap
                    },

                    //save with with pump text description
                    Text {
                        id: text11
                        x: 246
                        y: 118
                        width: 284
                        height: 42
                        color: "#ffffff"
                        text: "Click to save coordinate <br>with suction activated"
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: 20
                        styleColor: "#00000000"
                        horizontalAlignment: Text.AlignLeft
                        wrapMode: Text.WordWrap
                    }
                ]




            }

            //row layout to place auto and demo beneath manual
            RowLayout {
                Layout.fillHeight: false
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                spacing: 10

                //auto configuration groupbox
                GroupBox {
                    id: boxAutoConfig
                    width: 650
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
                    //auto groupbox content
                    contentData: [

                        //auto connect button
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

                        //auto activate button
                        Button {
                            id: btnActivateArmAuto
                            x: 111
                            y: 190
                            width: 100
                            height: 47
                            text: qsTr("Activate Arm")
                            anchors.horizontalCenterOffset: 0
                            anchors.horizontalCenter: parent.horizontalCenter
                            enabled: false
                        },

                        //auto stop button
                        Button {
                            id: btnStopArmAuto
                            x: 111
                            y: 190
                            width: 100
                            height: 47
                            text: qsTr("Disconnect Arm")
                            anchors.horizontalCenterOffset: 141
                            anchors.horizontalCenter: parent.horizontalCenter
                            enabled: false
                        },

                        //auto set height button
                        Button {
                            id: btnHeightFetch
                            x: 318
                            y: 40
                            width: 113
                            height: 38
                            text: "Set Height"
                            enabled: false
                            hoverEnabled: true;

                            //blue rounded button format
                            background: Rectangle {
                                id:heightBackground
                                color: "#2bb9ef"
                                radius: 20
                                border.width: 2

                            }

                        },

                        //set height text description
                        Text {
                            id: txtHeightFetch
                            x: 304
                            y: 12
                            color: "#ffffff"
                            text: "Set Item Height"
                            wrapMode: Text.WordWrap
                            font.pixelSize: 20
                            styleColor: "#00000000"
                        },

                        //auto set signature button
                        Button {
                            id: btnSignatureFetch
                            x: 158
                            y: 39
                            width: 113
                            height: 38
                            text: "Set Signature"
                            enabled: false
                            hoverEnabled: true;

                            //blue rounded button format
                            background: Rectangle {
                                id:signatureBackground
                                color: "#2bb9ef"
                                radius: 20
                                border.width: 2
                            }

                        },

                        //set signature text description
                        Text {
                            id: txtSignatureFetch
                            x: 139
                            y: 12
                            color: "#ffffff"
                            text: "Fetch Signature"
                            wrapMode: Text.WordWrap
                            font.pixelSize: 20
                            styleColor: "#00000000"
                        },

                        //set start position button
                        Button {
                            id: btnPositionStart
                            x: 94
                            y: 121
                            width: 113
                            height: 38
                            text: "Start Point"
                            enabled: false
                            hoverEnabled: true;

                            //blue rounded button format
                            background: Rectangle {
                                id:positionStartBackground
                                color: "#2bb9ef"
                                radius: 20
                                border.width: 2
                            }

                        },

                        //set stamper position button
                        Button {
                            id: btnStamperPosition
                            x: 232
                            y: 121
                            width: 113
                            height: 38
                            text: "Stamper Point"
                            enabled: false
                            hoverEnabled: true;

                            //blue rounded button format
                            background: Rectangle {
                                id:stamperBackground
                                color: "#2bb9ef"
                                radius: 20
                                border.width: 2
                            }


                        },

                        //set end position button
                        Button {
                            id: btnPositionEnd
                            x: 374
                            y: 121
                            width: 113
                            height: 38
                            text: "End Point"
                            enabled: false
                            hoverEnabled: true;

                            //blue rounded button format
                            background: Rectangle {
                                id:positionEndBackground
                                color: "#2bb9ef"
                                radius: 20
                                border.width: 2
                            }
                        },

                        //text description for the coordinates setting
                        Text {
                            id: txtPositions
                            x: 183
                            y: 90
                            color: "#ffffff"
                            text: "Set Movement Positions"
                            wrapMode: Text.WordWrap
                            font.pixelSize: 20
                            styleColor: "#00000000"
                        }
                    ]
                }

                //groubox for demo function
                GroupBox {
                    id: boxTroubleshoot
                    width: 442
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    Layout.fillWidth: false
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

                    //demo groupbox content
                    contentData: [

                        //button to execute demo function
                        Button {
                            id: btnDemo
                            x: 137
                            y: 188
                            width: 197
                            height: 47
                            text: qsTr("Arm Demo")
                            anchors.horizontalCenterOffset: 1
                            anchors.horizontalCenter: parent.horizontalCenter
                            background: Rectangle {
                                id: demoBackground
                                color: "#E0E0E0"
                            }

                        },

                        //text description about demo
                        Text {
                            id: txtDemoDescription
                            x: 0
                            y: 8
                            width: 438
                            height: 161
                            color: "#ffffff"
                            text: "In order to check for any movement fault, we recommend that you execute the demo. This will test the movement based on preset coordinates and vacuum function."
                            style: Text.Raised
                            anchors.horizontalCenter: parent.horizontalCenter
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            font.pixelSize: 20
                            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                            styleColor: "#00000000"
                        }]
                }
            }
        }

        //control panel title formatting
        Text {
            id: txtControlTitle
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
