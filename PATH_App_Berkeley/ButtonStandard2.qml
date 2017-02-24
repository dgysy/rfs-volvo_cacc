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
        id:buttonBG2
        width:myWidth
        height:myHeight
        border.width:3
        radius:120 //SY: the shape of button is round
        border.color:"#ffffff"

        //border.color:buttonColorLighter
        /*gradient:Gradient{
            GradientStop { position: 0; color: buttonColor }
            GradientStop { position: 1; color: buttonColorDarker }
        }*/

        //color:"#f7f7f7"
        color:"transparent"

  /*Text{
            id:buttonTxt
            text:btnText
            //color:"#071e29"
            color:"#ffffff"
            font.bold: true
            anchors.centerIn: parent
            font.family: "Volvo Sans Pro"
            font.pixelSize: 80 // SY: original is 40
            //contentWidth:0
        }*/




    /*DropShadow {
        color: "#aa000000"//"#00aaff"
        anchors.fill: buttonBG2
        horizontalOffset: 6
        verticalOffset: 6
        radius: 3.0
        //fast: false
        anchors.rightMargin: -6
        samples: 16
        source: buttonBG2
    }*/



    MouseArea{  // SY2: I changet the effect of pressing and releasing button
        anchors.fill:parent
        onPressed:{

       if (myID===2) {
            minusGapArrow.source="Images/Button/minusGap1.png"
            parent.scale=0.9
        } else if(myID===3){
          addGapArrow.source="Images/Button/addGap1.png"
          parent.scale=1.1
         }
        }

        onReleased:{
            parent.scale=1
           if (myID===2) {
                minusGapArrow.source="Images/Button/minusGap.png"
              } else if(myID===3){
               addGapArrow.source="Images/Button/addGap.png"

            }
                 if(parent.opacity===1){
                buttonClicked(myGroup,myID)
            }
        }
    }

 }
}
