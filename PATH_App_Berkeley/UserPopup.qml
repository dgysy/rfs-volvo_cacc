import QtQuick 2.5
import QtGraphicalEffects 1.0

Item{
    id:popupHolder
    width:popupBG.width+10
    height:popupBG.height+10
    anchors.centerIn: parent
    anchors.verticalCenterOffset: -100
    visible:opacity>0

    property string btnOneText:"YES"
    property string btnTwoText:"NO"
    property string popupMainText:"LEAVE STRING?"
    property string popupSubText:"Fuel saved: XX gal/mile"
    property var popupData:[
        ["","",""],
        ["DISSOLVE PLATOON?","Leave all your friends behind...","YES","NO"],
        ["LEAVE STRING?","Fuel saved: XX gal/mile","YES","NO"]]
    property int currentPopupID:0

    onCurrentPopupIDChanged:{
        console.log(currentPopupID)
        popupMainText= popupData[currentPopupID][0]
        popupSubText=popupData[currentPopupID][1]
        btnOneText= popupData[currentPopupID][2]
        btnTwoText= popupData[currentPopupID][3]
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
        Text{
            id:popupBreadText
            text:popupSubText
            color:"#FFFFFF"
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top:popupHeadlineText.bottom
            anchors.topMargin: 20
            font.family: "Volvo Sans Pro"
            font.pixelSize: 40
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
            myID:isLeader ? 2 : 3
            btnText: btnOneText

        }
        ButtonStandard{
            id:abortPopupBtn
            myGroup:0
            myID:2
            btnText: btnTwoText
        }

    }



}

