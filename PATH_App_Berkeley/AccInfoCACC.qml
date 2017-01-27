import QtQuick 2.3

import QtGraphicalEffects 1.0

Item{
    id:accInfo
    height:400
    width:400

    property bool targetDetected:udpXDataCACC.CACCTargetActive
    property real ccEnabladOpacityLevel:0.5


    property bool cruiseChangedActive:false
    property int cruiseChangedValue:0

    property int adjustedCACCGap: udpXDataCACC.CACCDegraded===1 ? Math.max(udpXDataCACC.CACCTimeGap,1) :udpXDataCACC.CACCTimeGap
    property int adjustedACCGap: udpXDataCACC.CACCDegraded===1 ? Math.max(udpXDataCACC.ACCTimeGap,1) :udpXDataCACC.ACCTimeGap
    property bool forwardCollisionWarning:udpXDataCACC.CACCEvents===1
    property bool brakeCapacityWarning:udpXDataCACC.CACCEvents===2
    property bool laneChangeLeft: udpXDataCACC.CACCEvents===3
    property bool laneChangeRight: udpXDataCACC.CACCEvents===4
    property bool obstacleAhead: udpXDataCACC.CACCEvents===5
    property bool connectionLost: udpXDataCACC.CACCEvents===6

    property int caccEvent:udpXDataCACC.CACCEvents

    property int platooningState:udpXDataCACC.platooningState
    property string platooningStateString: "CACC"

    property var audioCaccEvent:[-1,5,5,1,1,0,0,0]

    property int accState:udpXDataCACC.CACCState
    property string accText:""

    onAccStateChanged: {
        var temp=["","CACC","CACC","ACC","ACC"]
        accText=temp[accState]
    }

    onPlatooningStateChanged: {
        var temp=["CACC","JOINING","LEAVING","","DISSOLVING",""]
        platooningStateString=temp[platooningState]
    }

    onCaccEventChanged: {
        var newSound=audioCaccEvent[caccEvent]
        if(newSound>-1){
            //audioPlayer.playAudio(newSound)
        }
    }

    function activeCruise(){
        if(accState===2){
            return(true)
        }else if(accState===4){
            return (true)
        }
        return(false)
    }

    function targetCruise(){
        if(accState>0 && udpXDataCACC.CACCTargetActive){
            return(true)
        }
        return(false)
    }

    function connectionCruise(){
        if(accState>0 && accState<3){
            if(udpXDataCACC.CACCActiveConnectionToTarget >0 || udpXDataCACC.CACCActiveConnectionFromTarget){
                return(true)
            }else{
                return(false)
            }
        }else{
            return(false)
        }
    }

    onConnectionLostChanged: {
        if(connectionLost){
            wifiLostAnimation.restart()
        }
    }

    onLaneChangeLeftChanged: {
        if(laneChangeLeft){
            laneChangeAnimationLeft.restart()
        }
    }

    onLaneChangeRightChanged: {
        if(laneChangeRight){
            laneChangeAnimationRight.restart()
        }
    }

    onObstacleAheadChanged: {
        if(obstacleAhead){
            obstacleAheadAnimation.restart()
        }
    }


    Item{
        id:cruiseIcon
        anchors.centerIn:parent
        anchors.horizontalCenterOffset:-6
        visible:accState >0
        Image{
            id:ccLanes
            anchors.centerIn:parent
            opacity:activeCruise()? 1 : ccEnabladOpacityLevel
            source:accState > 2 ? "Images/Cruise/ccLanesGrey.png" : "Images/Cruise/ccLanesBlue.png"
        }
        Item{
            id:laneChangeHolder
            width:laneChangeLeftImage.width+laneChangeRightImage.width
            height:laneChangeRightImage.height
            anchors.centerIn:parent
            visible:laneChangeLeft||laneChangeRight
            Image{
                id:laneChangeLeftImage
                source:"Images/CACC/laneChangeLeft.png"
                anchors.left:parent.left
                anchors.leftMargin: 14
                visible:laneChangeLeft
            }
            Image{
                id:laneChangeRightImage
                source:"Images/CACC/laneChangeRight.png"
                anchors.right:parent.right
                anchors.rightMargin: 14
                visible:laneChangeRight

            }
            SequentialAnimation {
                id:laneChangeAnimationLeft
                loops: 1
                NumberAnimation {
                    target: laneChangeLeftImage
                    property: "opacity"
                    from: 0.2
                    to:1
                    duration: 300
                    easing.type: Easing.InOutQuad
                }
                NumberAnimation {
                    target: laneChangeLeftImage
                    property: "opacity"
                    from: 1
                    to:0.2
                    duration: 500
                    easing.type: Easing.InOutQuad
                }
                onRunningChanged: {
                    if(this.running){
                    }else{
                        if(laneChangeLeft){
                            laneChangeAnimationLeft.restart()
                        }
                    }
                }
            }
            SequentialAnimation {
                id:laneChangeAnimationRight
                loops: 1
                NumberAnimation {
                    target: laneChangeRightImage
                    property: "opacity"
                    from: 0.2
                    to:1
                    duration: 300
                    easing.type: Easing.InOutQuad
                }
                NumberAnimation {
                    target: laneChangeRightImage
                    property: "opacity"
                    from: 1
                    to:0.2
                    duration: 500
                    easing.type: Easing.InOutQuad
                }
                onRunningChanged: {
                    if(this.running){
                    }else{
                        if(laneChangeRight){
                            laneChangeAnimationRight.restart()
                        }
                    }
                }
            }
        }

        Image{
            id:ccGap
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: ccLanes.bottom
            //anchors.centerIn:parent
            anchors.verticalCenterOffset: 30
            opacity:activeCruise()? 1 : ccEnabladOpacityLevel
            source:accState>2 ? "Images/Cruise/ccGapGrey.png" : "Images/Cruise/ccGapBlue.png"
            clip:true
            fillMode: Image.Pad
            verticalAlignment: Image.AlignBottom
            property var clipping:[25,42,58,70,80]
            height:accState>2 ? clipping[adjustedACCGap] : clipping[adjustedCACCGap]
            Item{
                id:degradedBrakesHolder
                width:degradedBrakesBlocker.width
                height:degradedBrakesBlocker.height
                anchors.bottom:parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                Rectangle{
                    id:degradedBrakesBlocker
                    opacity:0.7
                    width:156
                    height:42
                    color:"#20282d"
                    visible:udpXDataCACC.CACCDegraded===1
                }
            }
        }

        Image{
            id:degradedIcon
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: ccGap.bottom
            anchors.bottomMargin:-2
            source:"Images/CACC/iconDegradedBrakes.png"
            visible:udpXDataCACC.CACCDegraded===1
        }

        Rectangle{
            id:obstacleAheadIcon
            width:ccTarget.width-10
            height:width
            anchors.centerIn: ccTarget
            anchors.verticalCenterOffset: -4
            visible:obstacleAhead
            SequentialAnimation {
                id:obstacleAheadAnimation
                loops: 1
                NumberAnimation {
                    target: obstacleAheadIcon
                    property: "opacity"
                    from: 0.2
                    to:1
                    duration: 300
                    easing.type: Easing.InOutQuad
                }
                NumberAnimation {
                    target: obstacleAheadIcon
                    property: "opacity"
                    from: 1
                    to:0.2
                    duration: 500
                    easing.type: Easing.InOutQuad
                }
                onRunningChanged: {
                    if(this.running){
                    }else{
                        if(obstacleAhead){
                            obstacleAheadAnimation.restart()
                        }
                    }
                }
            }
        }

        Image{
            id:ccTarget
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: ccGap.top
            anchors.bottomMargin: 5
            scale:(4-udpXDataCACC.CACCTimeGap)*0.08+1
            source:accState > 2 ? "Images/Cruise/ccTargetGrey.png" :"Images/Cruise/ccTargetBlueTruck.png"
            visible:targetCruise()
            opacity:(activeCruise()? 1 : ccEnabladOpacityLevel)
        }
        Item{
            id:ccWifiContainer
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -76
            visible:connectionCruise() && !connectionLost
            opacity:(accState===2 ? 1 : ccEnabladOpacityLevel)

            Image{
                id:ccWifiDot
                anchors.centerIn:parent
                source:"Images/Cruise/ccWifiDotBlue.png"
            }
            Image{
                id:ccWifi
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom:ccWifiDot.top
                anchors.bottomMargin:0
                source:"Images/Cruise/ccWifiBlue.png"
            }
        }

        Item{
            id:ccConnectionLostContainer
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -96
            visible:udpXDataCACC.CACCEvents===6
            opacity:1//(accState===2 ? 1 : ccEnabladOpacityLevel)

            Image{
                id:ccWifiLostX
                anchors.centerIn:parent
                source:"Images/CACC/iconConnectionLostBlue.png"
            }
//            Image{
//                id:ccWifiLostCross
//                anchors.centerIn:parent
//                source:"Images/CACC/iconConnectionLostCross.png"
//            }
            SequentialAnimation {
                id:wifiLostAnimation
                loops: 1
                NumberAnimation {
                    target: ccConnectionLostContainer
                    property: "opacity"
                    from: 0.2
                    to:1
                    duration: 300
                    easing.type: Easing.InOutQuad
                }
                NumberAnimation {
                    target: ccConnectionLostContainer
                    property: "opacity"
                    from: 1
                    to:0.2
                    duration: 500
                    easing.type: Easing.InOutQuad
                }
                onRunningChanged: {
                    if(this.running){
                    }else{
                        if(connectionLost){
                            wifiLostAnimation.restart()
                        }
                    }
                }
            }
        }
        Item{
            id:accStateTextHolder
            width:70
            height:60
            anchors.top:ccLanes.bottom
            anchors.topMargin:2
            anchors.horizontalCenter: parent.horizontalCenter
            Text{
                id:accStateText
                font.family: fontBold
                font.bold:true
                font.pointSize: isAndroid ? 26 : 32
                text:accState>2 ?  accText : platooningStateString
                horizontalAlignment: Text.AlignHCenter
                anchors.centerIn: parent
                opacity: activeCruise()? 1 : ccEnabladOpacityLevel
                color:accState>2 ? fontInstrumentColor : "#007dc8"
            }

        }

        Item{
            id:caccEventsTextHolder
            width:70
            height:60
            anchors.top:accStateTextHolder.bottom
            anchors.topMargin:-10
            anchors.horizontalCenter: parent.horizontalCenter
            Text{
                property var popupStrings:["",
                    "Forward Collision Warning",
                    "Brake Capacity Warning",
                    "Lane change ahead",
                    "Lane change ahead",
                    "Obstacle ahead",
                    "CACC connection lost",
                    "Brakes overheated"]
                id:caccEventText
                font.family: volvoFontSansMedium.name
                font.pointSize: isAndroid ? 24 : 30
                text:udpXDataCACC.CACCEvents===0 ? (udpXDataCACC.CACCDegraded>0 ? popupStrings[7] : "") : popupStrings[udpXDataCACC.CACCEvents]
                horizontalAlignment: Text.AlignHCenter
                anchors.centerIn: parent
                opacity: 1
                color:"#FFFFFF"
            }
//            ColorOverlay {
//                anchors.fill: caccEventText
//                source: caccEventText
//                color: "#FFFF0000"
//                //visible:forwardCollisionWarning
//            }

        }
        Item{
            id:platooningStateTextHolder
            width:70
            height:60
            anchors.top:accStateTextHolder.bottom
            anchors.topMargin:-10
            anchors.horizontalCenter: parent.horizontalCenter
            Text{
                property var platooningStateStrings:["",
                    "Joining platoon",
                    "Take over and wait for gap",
                    "You have left the platoon",
                    "Take over and wait for gap",
                    "CACC dissolved"]
                id:platooningStateText
                font.family: volvoFontSansMedium.name
                font.pointSize: isAndroid ? 24 : 30
                text:udpXDataCACC.CACCEvents===0 ? platooningStateStrings[udpXDataCACC.platooningState] : ""
                horizontalAlignment: Text.AlignHCenter
                anchors.centerIn: parent
                opacity: 1

                color:"#FFFFFF"
            }
//            ColorOverlay {
//                anchors.fill: caccEventText
//                source: caccEventText
//                color: "#FFFF0000"
//                //visible:forwardCollisionWarning
//            }

        }

    }



}
