import QtQuick 2.5

Item{
    id:waitingHolder
    anchors.fill:parent
    opacity:popupID<1 ? (platooningState<2 ? 1 : 0) : 0
    scale:popupID<1 ? (platooningState<2 ? 1: 1.2) : 1.2
    visible:opacity>0

    Behavior on opacity{
        SpringAnimation{damping:1;spring:5}
    }
    Behavior on scale{
        SpringAnimation{damping:1;spring:5}
    }

    Text{
        id:waitingTxt
        text:"Searching for string"
        color:"#FFFFFF"
        font.bold: true
        anchors.centerIn: parent
        font.family: "Volvo Sans Pro"
        font.pixelSize: 48
        anchors.verticalCenterOffset: -100
    }
    Rectangle{
        id:waiting
        width:150
        height:width
        radius:width/2
        color:"#00000000"
        border.width: 10
        border.color: "#FFFFFF"
        anchors.centerIn: parent
        SequentialAnimation {
            running: waitingHolder.visible
            loops:Animation.Infinite
            ParallelAnimation{
                NumberAnimation { target: waiting; property: "opacity"; from:0.8;to: 0.2; duration: 2000;easing {type: Easing.InOutQuad; } }
                NumberAnimation { target: waiting; property: "scale"; from:0.8;to: 0.2; duration: 2000;easing {type: Easing.InOutQuad;} }
            }
        }

    }

    Rectangle{
        id:waiting2
        width:150
        height:width
        radius:width/2
        color:"#00000000"
        border.width: 10
        border.color: "#FFFFFF"
        anchors.centerIn: parent
        SequentialAnimation {
            running: waitingHolder.visible
            loops:Animation.Infinite
            ParallelAnimation{
                NumberAnimation { target: waiting2; property: "opacity"; from:0.2;to: 0.8; duration: 2000;easing {type: Easing.InOutQuad;}}
                NumberAnimation { target: waiting2; property: "scale"; from:0.2;to: 0.8; duration: 2000;easing {type: Easing.InOutQuad;}}
            }
        }

    }
}

