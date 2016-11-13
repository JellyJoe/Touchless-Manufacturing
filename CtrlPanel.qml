import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.2

CtrlPanelForm {


    //========================================================================================
    //                                      MANUAL

    //stop the manual process
    btnStopArmManual.onClicked: _myArm.stopMovement()

    //activate the manual process
    btnActivateArmManual.onClicked: _myArm.executeManualMovement()

    //establish connection with arm for manual process
    btnConnectManual.onClicked: _myArm.manualLuanched()



    /*----- Move with pump button configuration -----*/

    //store coordinate with suction active
    btnMoveWithPump.onClicked: _myArm.saveWithPump()

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
    btnMoveWithoutPump.onClicked: _myArm.saveWithoutPump()

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
    btnSignatureFetch.onClicked:_myClass.pixyRun()

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
    btnDemo.onClicked:_myArm.demoClicked()



}
