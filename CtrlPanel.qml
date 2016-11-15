import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.2

CtrlPanelForm {

    // REFERENCE
    // http://doc.qt.io/qt-5/qml-qtquick-controls2-textarea-members.html
    txtManualMoveRecord.readOnly: true
    txtManualMoveRecord.textFormat: TextEdit.RichText // for color


    //========================================================================================
    //                                      MANUAL

    //stop the manual process
    btnStopArmManual.onClicked:{
        txtManualMoveRecord.append("<font color=\"red\">MANUAL: Stopped arm movement</font>")
        _myArm.stopMovement()
        //change the color of  start to yellow
        connectManualBackground.color = "#E0E0E0"

    }


    //activate the manual process
    btnActivateArmManual.onClicked:
    {
        txtManualMoveRecord.append("MANUAL: Activated arm movement")
        _myArm.executeManualMovement()
    }

    /*----- Establish manual connection -----*/

    //establish connection with arm for manual process
    btnConnectManual.onClicked:{
        txtManualMoveRecord.append("MANUAL: Connected arm movement")
         _myArm.manualLaunched()
        //change button color to green
        connectManualBackground.color = "#67f90c"
    }



    /*----- Move with pump button configuration -----*/

    //store coordinate with suction active
    btnMoveWithPump.onClicked: {
        txtManualMoveRecord.append("MANUAL: Stored coordinates with suction activation")
        _myArm.saveWithPump()
    }

    //lighter colour onclick
    btnMoveWithPump.onPressed: {
        withPumpBackground.color = "#68ccf2"
    }
    //original colour upon release
    btnMoveWithPump.onReleased: {
        withPumpBackground.color = "#2bb9ef"
    }


    /*----- Move with without pump button configuration -----*/

    //store coordinate without suction
    btnMoveWithoutPump.onClicked:
    {
        txtManualMoveRecord.append("MANUAL: Stored coordinates only")
        _myArm.saveWithoutPump()
    }

    //lighter colour onclick
    btnMoveWithoutPump.onPressed: {
        withoutPumpBackground.color = "#68ccf2"
    }
    //original colour upon release
    btnMoveWithoutPump.onReleased: {
        withoutPumpBackground.color = "#2bb9ef"

    }


    //========================================================================================
    //                                      AUTOMATIC

    /*----- Signature button configuration -----*/

    //run pixymon to fetch signature of item
    btnSignatureFetch.onClicked:
    {
        txtManualMoveRecord.append("AUTOMATIC: This shit good!!!")
        _myClass.pixyRun()
    }

    //lighter colour onclick
    btnSignatureFetch.onPressed: {
        signatureBackground.color = "#68ccf2"
    }
    //original colour upon release
    btnSignatureFetch.onReleased: {
        signatureBackground.color = "#2bb9ef"
    }


    /*----- Store the stamper position -----*/

    //lighter colour onclick
    btnStamperPosition.onPressed: {
        stamperBackground.color = "#68ccf2"

    }
    //original colour upon release
    btnStamperPosition.onReleased: {
        stamperBackground.color = "#2bb9ef"
    }


    /*----- Store the end position -----*/

    //lighter colour onclick
    btnPositionEnd.onPressed: {
        positionEndBackground.color = "#68ccf2"
    }
    //original colour upon release
    btnPositionEnd.onReleased: {
        positionEndBackground.color = "#2bb9ef"
    }

    //========================================================================================
    //                                      DEMO

    //execute demo movemement for arm
    btnDemo.onClicked:
    {
        txtManualMoveRecord.append("DEMO: Running...")
        _myArm.demoClicked()
    }


}
