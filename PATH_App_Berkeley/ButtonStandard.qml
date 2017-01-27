import QtQuick 2.5
import QtGraphicalEffects 1.0

Item{
    id:buttonHolder
    property int myWidth:240
    property int myHeight:80
    property int myID:-1
    property int myGroup:-1
    property string btnText:"VOID"
    height:myHeight+10
    width:myWidth+10

    Rectangle{
        id:buttonBG
        width:myWidth
        height:myHeight
        border.width:1
        radius:6
        border.color:buttonColorLighter
        gradient:Gradient{
            GradientStop { position: 0; color: buttonColor }
            GradientStop { position: 1; color: buttonColorDarker }
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
            if(parent.opacity===1){
                buttonClicked(myGroup,myID)
            }
        }
    }

}
