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
        radius:120 //SY: the shape of button is round

        // border.color:buttonColorLighter
        /*gradient:Gradient{
            GradientStop { position: 0; color: buttonColor }
            GradientStop { position: 1; color: buttonColorDarker }
        }*/

        color:"#f7f7f7"

        Text{
            id:buttonTxt
            text:btnText
            color:"#071e29"
            font.bold: true
            anchors.centerIn: parent
            font.family: "Volvo Sans Pro"
            font.pixelSize: 60 // SY: original is 40
            //contentWidth:0
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
        color: "#aa000000"//"#00aaff"
        anchors.fill: buttonBG2
        horizontalOffset: 6
        verticalOffset: 6
        radius: 3.0
        //fast: false
        anchors.rightMargin: -6
        samples: 16
        source: buttonBG2
    }

    MouseArea{
        anchors.fill:parent
        onPressed:{
            parent.scale=1.1
            buttonBG2.color="#ffffff"
        }
        onReleased:{
            parent.scale=1
            buttonBG2.color="#f7f7f7"
            if(parent.opacity===1){
                buttonClicked(myGroup,myID)
            }
        }
    }

}
