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
            color:"#ffffff"
            font.bold: true
            anchors.centerIn: parent
            font.family: "Volvo Sans Pro"
            font.pixelSize: 65 // original is 40
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
        anchors.fill: buttonBG
        horizontalOffset: 1
        verticalOffset: 1
        radius: 2.0
        fast: false
        anchors.rightMargin: -6
        samples: 16
        source: buttonBG
    }

    MouseArea{
        anchors.fill:parent
        onPressed:{

            if (myID==1){
            cAccBtn.scale=1.1
            accBtn.scale=1.0
            cAccBtn.opacity=1.0
            accBtn.opacity=0.5
            }

            if(myID==0){
                cAccBtn.scale=1.0
                accBtn.scale=1.1
                cAccBtn.opacity=0.5
                accBtn.opacity=1.0

            }
        }
        onReleased:{
            //parent.scale=1
            if(parent.opacity===1){  // Why we need to use an 'if' command here?
                buttonClicked(myGroup,myID)
            }
          }


    }

}
