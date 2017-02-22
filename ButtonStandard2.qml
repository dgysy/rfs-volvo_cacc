import QtQuick 2.5
import QtGraphicalEffects 1.0

// creat a round button

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
        id:buttonBG2
        width:myWidth
        height:myHeight
        border.width:1
        radius:120
        border.color:"#FFFFFF"
        // border.color:buttonColorLighter
        /*gradient:Gradient{
            GradientStop { position: 0; color: buttonColor }
            GradientStop { position: 1; color: buttonColorDarker }
        }*/
        color:"transparent"

        Text{
            id:buttonTxt
            text:btnText
            color:"#ffffff"
            font.bold: true
            anchors.centerIn: parent
            font.family: "Volvo Sans Pro"
            font.pixelSize: 70 // original is 40
        }
       /* DropShadow {
            anchors.fill: buttonTxt
            horizontalOffset: 3
            verticalOffset: 3
            radius: 8.0
            anchors.rightMargin: -31
            samples: 16
            color: "#ffffff"
            source: buttonTxt
        }*/
    }
    DropShadow {
        color: "#00aaff"
        anchors.fill: buttonBG2
        horizontalOffset: 1
        verticalOffset: 1
        radius: 2.0
        fast: false
        anchors.rightMargin: -6
        samples: 16
        source: buttonBG2
    }

    MouseArea{
        anchors.fill:parent
        onPressed:{
            parent.scale=1.2
        }
        onReleased:{
            parent.scale=1
            if(parent.opacity===1){
                buttonClicked(myGroup,myID)
            }
        }
    }

}
