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
        radius:10
        border.color:buttonColorLighter
        gradient:Gradient{
            GradientStop { position: 0; color: buttonColor }
            GradientStop { position: 1; color: buttonColorDarker }
        }

        Text{
            id:buttonTxt
            width: 170
            height: 78
            text:btnText
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color:"#ffffff"
            //font.bold: true
            anchors.centerIn: parent
            font.family: "Volvo Sans Pro"
            font.pixelSize: 60 // SY: the size of button originally is 40
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
        anchors.fill: buttonBG
        horizontalOffset: 6
        verticalOffset: 6
        radius: 2.0
        fast: false
        anchors.rightMargin: -6
        samples: 16
        source: buttonBG
    }

    MouseArea{
        anchors.rightMargin: 10
        anchors.bottomMargin: 8
        anchors.leftMargin: -5
        anchors.topMargin: 0
        anchors.fill:parent
        onPressed:{

            if (myID==1){
            cAccBtn.scale=1.1
            accBtn.scale=1.0
            cAccBtn.opacity=1.0
            accBtn.opacity=0.3
            }

            if(myID==0){
                cAccBtn.scale=1.0
                accBtn.scale=1.1
                cAccBtn.opacity=0.3
                accBtn.opacity=1.0

            }
        }
        onReleased:{
            //parent.scale=1
            if(parent.opacity===1){
                buttonClicked(myGroup,myID)
            }
          }


    }

}
