import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.2

CtrlPanelForm {

    property color hoverColor: "#aaaaaa"
    property color pressColor: "slategray"


    //execute demo movemement for arm
    btnDemo.onClicked:_myClass.demoClicked()

    //run pixymon to fetch signature of item
    btnSignatureFetch.onClicked:_myClass.pixyRun()



}
