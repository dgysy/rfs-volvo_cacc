import QtQuick 2.5
import QtGraphicalEffects 1.0

Item{
    id:buttonHolder
    property int myWidth:240
    property int myHeight:80
    property int myID:-1
    property int myGroup:-1
    property string btnText:"VOID"
    property int myState:0 //0=off, 1=Enabled, 2=Active
    height:myHeight+10
    width:myWidth+10

    Rectangle{
        id:buttonBG
        width:myWidth
        height:myHeight
        border.width:1
        radius:6
        border.color:myState ===0 ? buttonColorLighter : buttonActiveColorLighter
        gradient:Gradient{
            GradientStop { position: 0; color: myState===2 ? buttonActiveColor:buttonColor }
            GradientStop { position: 1; color: myState===2 ? buttonActiveColorDarker :buttonColorDarker }
        }

        Text{
            id:buttonTxt
            text:btnText
            color:"#FFFFFF"
            font.bold: true
            anchors.centerIn: parent
            font.family: "Volvo Sans Pro"
            font.pixelSize: 40
        }
        DropShadow {
            anchors.fill: buttonTxt
            horizontalOffset: 3
            verticalOffset: 3
            radius: 8.0
            samples: 16
            color: "#80000000"
            source: buttonTxt
        }
    }
    DropShadow {
        anchors.fill: buttonBG
        horizontalOffset: 3
        verticalOffset: 3
        radius: 8.0
        samples: 16
        color: "#80000000"
        source: buttonBG
    }

    MouseArea{
        anchors.fill:parent
        onPressed:{
            parent.scale=1.1
        }
        onReleased:{
            parent.scale=1
            buttonClicked(myGroup,myID)
        }
    }

}
