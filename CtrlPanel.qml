import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.2

CtrlPanelForm
{



    // REFERENCE
    // http://doc.qt.io/qt-5/qml-qtquick-controls2-textarea-members.html
    txtManualMoveRecord.readOnly: true
    txtManualMoveRecord.textFormat: TextEdit.RichText // for color


    property int signaturePresent



    //========================================================================================
    //                                      MANUAL


    /*----- Establish manual connection -----*/

    //establish connection with arm for manual process
    btnConnectManual.onClicked:
    {
        txtManualMoveRecord.append("MANUAL: Connected arm movement")
         _myArm.manualLaunched()

        //change button color to green
        connectManualBackground.color = "#67f90c"

        //disable auto buttons
        btnActivateArmAuto.enabled = false
        btnSignatureFetch.enabled = false
        btnStamperPosition.enabled = false
        btnPositionEnd.enabled = false
        btnStopArmAuto.enabled = false
        btnPositionStart.enabled = false
        btnHeightFetch.enabled = false

        //disable the auto and demo button
        btnConnectAuto.enabled = false
        btnDemo.enabled = false

        //enable manual buttons
        btnActivateArmManual.enabled = true
        btnStopArmManual.enabled = true
        btnMoveWithPump.enabled =  true
        btnMoveWithoutPump.enabled = true

    }

    /*----- Manual activate button configuration  -----*/
    btnActivateArmManual.onClicked:
    {
        txtManualMoveRecord.append("MANUAL: Activated arm movement")
        _myArm.executeManualMovement()
    }


    /*----- Manual Stop button configuration  -----*/
    btnStopArmManual.onClicked:
    {
        txtManualMoveRecord.append("<font color=\"red\">MANUAL: Stopped arm movement</font>")
        _myArm.stopMovement()

        //change the color of  start to grey
        connectManualBackground.color = "#E0E0E0"

        //activate the auto and demo connect buttons
        btnConnectAuto.enabled = true
        btnDemo.enabled = true
    }

    /*----- Move with pump button configuration -----*/

    //store coordinate with suction active
    btnMoveWithPump.onClicked:
    {
        txtManualMoveRecord.append("MANUAL: Stored coordinates with suction activation")
        _myArm.saveWithPump()
    }

    //lighter colour onclick
    btnMoveWithPump.onPressed:
    {
        withPumpBackground.color = "#68ccf2"
    }

    //original colour upon release
    btnMoveWithPump.onReleased:
    {
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
    btnMoveWithoutPump.onPressed:
    {
        withoutPumpBackground.color = "#68ccf2"
    }

    //original colour upon release
    btnMoveWithoutPump.onReleased:
    {
        withoutPumpBackground.color = "#2bb9ef"
    }

    //========================================================================================
    //                                      AUTOMATIC


    /*----- Auto connect enable button configuration  -----*/
    btnConnectAuto.onClicked:
    {

        txtManualMoveRecord.append("MANUAL: Connected arm movement")
        // _myArm.autoLaunched()


        //change button color to green
        connectAutoBackground.color = "#67f90c"

        //disable manual buttons
        btnActivateArmManual.enabled = false
        btnStopArmManual.enabled = false
        btnMoveWithPump.enabled =  false
        btnMoveWithoutPump.enabled = false

        //disable the manual and demo button
        btnConnectManual.enabled = false
        btnDemo.enabled = false

        //enable auto buttons
        btnActivateArmAuto.enabled = true
        btnSignatureFetch.enabled = true
        btnStamperPosition.enabled = true
        btnPositionEnd.enabled = true
        btnStopArmAuto.enabled = true
        btnPositionStart.enabled = true
        btnHeightFetch.enabled = true

    }

    /*----- Auto activate button configuration  -----*/
    btnActivateArmAuto.onClicked:
    {
        //start the time
        _myArm.executeTime()
        txtManualMoveRecord.append("Auto: Activated arm movement")

        //start connection to pixy
        _myPixy.getBlocks()

        //execute loop while there is no signature detected
        while(!_myPixy.checkBlocks())
        {
            if(!_myPixy.checkBlocks())
            {
                //execute the arm
                _myArm.executeAutoMovement()
            }

            else
            {
                //break loop the moment signature is detected
                break
            }
        }

        //reset pixy connection to flush out buffer
        _myPixy.stopPixy()

    }

    /*----- Auto stop button configuration -----*/
    btnStopArmAuto.onClicked:
    {
        //stop arm connection
        _myArm.stopMovement();

        //stop pixy connection
        _myPixy.stopPixy()

        //change the connect button to grey
        connectAutoBackground.color = "#E0E0E0"

        //disable the auto and demo button
        btnConnectManual.enabled = true
        btnDemo.enabled = true
    }


    /*----- Signature button configuration -----*/

    //run pixymon to fetch signature of item
    btnSignatureFetch.onClicked:
    {
        txtManualMoveRecord.append("AUTOMATIC: Signature assign")
        _myPixy.executePixymon()
    }

    //lighter colour onclick
    btnSignatureFetch.onPressed:
    {
        signatureBackground.color = "#68ccf2"
    }

    //original colour upon release
    btnSignatureFetch.onReleased:
    {
        signatureBackground.color = "#2bb9ef"
    }

    /*----- Height button configuration -----*/

    //onclick
    btnHeightFetch.onClicked:
    {
        //call function to set heigh of item
        _myArm.setHeight();
        txtManualMoveRecord.append("AUTOMATIC: Height assign")
    }

    //lighter colour onclick
    btnHeightFetch.onPressed:
    {
        heightBackground.color = "#68ccf2"
    }

    //original colour upon release
    btnHeightFetch.onReleased:
    {
        heightBackground.color = "#2bb9ef"
    }

    /*----- Store the start position -----*/

    //button onclick
    btnPositionStart.onClicked:
    {
        _myArm.setPositionA();
    }

    //lighter colour onclick
    btnPositionStart.onPressed:
    {
        positionStartBackground.color = "#68ccf2"
    }
    //original colour upon release
    btnPositionStart.onReleased:
    {
        positionStartBackground.color = "#2bb9ef"
    }

    /*----- Store the stamper position -----*/

    //button onclick
    btnStamperPosition.onClicked:
    {
        _myArm.setPositionB();
    }

    //lighter colour onclick
    btnStamperPosition.onPressed:
    {
        stamperBackground.color = "#68ccf2"
    }
    //original colour upon release
    btnStamperPosition.onReleased:
    {
        stamperBackground.color = "#2bb9ef"
    }

    /*----- Store the end position -----*/

    //button onclick
    btnPositionEnd.onClicked:
    {
        _myArm.setPositionC();
    }

    //lighter colour onclick
    btnPositionEnd.onPressed:
    {
        positionEndBackground.color = "#68ccf2"
    }

    //original colour upon release
    btnPositionEnd.onReleased:
    {
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
