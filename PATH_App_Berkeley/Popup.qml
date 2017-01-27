import QtQuick 2.5
import QtGraphicalEffects 1.0

Item{
    id:popupHolder
    width:popupBG.width+10
    height:popupBG.height+10
    anchors.centerIn: parent
    anchors.verticalCenterOffset: -100
    visible:opacity>0

    property string btnOneText:"JOIN"
    property string btnTwoText:"IGNORE"
    property string popupMainText:"PLATOON FOUND"
    property var popupData:[["","",""],["PLATOON FOUND","JOIN","IGNORE"]]
    property int currentPopupID:0

    onCurrentPopupIDChanged:{
        popupMainText= popupData[currentPopupID][0]
        btnOneText= popupData[currentPopupID][1]
        btnTwoText= popupData[currentPopupID][2]

    }

    Behavior on opacity {
        SpringAnimation{
            damping:1
            spring:5
        }
    }
    Behavior on scale {
        SpringAnimation{
            damping:1
            spring:5
        }
    }
    Rectangle{
        id:popupBG
        width:900
        height:349
        border.width:1
        radius:12
        border.color:buttonColorLighter
        opacity:0.6
        gradient:Gradient{
            GradientStop { position: 0; color: popupColor }
            GradientStop { position: 1; color: popupColorDarker }
        }
    }
    Rectangle{
        id:popupBG2
        width:900
        height:349
        border.width:1
        radius:12
        border.color:buttonColorLighter
        opacity:1
        color:"#00000000"
    }
//    DropShadow {
//        anchors.fill: popupBG
//        horizontalOffset: 3
//        verticalOffset: 3
//        radius: 8.0
//        samples: 16
//        color: "#80000000"
//        source: popupBG
//        opacity: 0.6
//    }
    Item{
        id:popupTextHolder
        anchors.centerIn: parent
        width:popupBG.width
        height:popupBG.height
        Text{
            id:popupHeadlineText
            text:popupMainText
            color:"#FFFFFF"
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top:parent.top
            anchors.topMargin: 5
            font.family: "Volvo Sans Pro"
            font.pixelSize: 60

        }
        Row{
            id:destinationRow
            spacing: 20
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top:popupHeadlineText.bottom
            anchors.topMargin: 10
            visible:currentPopupID===1
            Image{
                source:"Images/destinationBig.png"
            }
            Text{
                id:popupTextFirstLine
                text:"Gothenburg"
                color:"#FFFFFF"
                font.bold: true
                font.family: "Volvo Sans Pro"
                font.pixelSize: 50
            }
        }

        Row{
            spacing:20
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top:destinationRow.bottom
            anchors.topMargin: 10
            visible:currentPopupID===1
            Text{
                id:popupTextLines
                text:"Leader rating:"
                color:"#FFFFFF"
                font.bold: true
                font.family: "Volvo Sans Pro"
                font.pixelSize: 40
            }
            StarRating{
                starSource: "Images/ratingStarBig.png"
                strokeSource:"Images/ratingStarBigStroke.png"
                myRating: 4
            }
        }
    }

    Row{
        id:popupButtonRow
        spacing:50
        anchors.bottom:parent.bottom
        anchors.bottomMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        ButtonStandard{
            id:joinPopupBtn
            myGroup:1
            myID:0
            btnText: btnOneText

        }
        ButtonStandard{
            id:abortPopupBtn
            myGroup:1
            myID:1
            btnText: btnTwoText
        }

    }



}

