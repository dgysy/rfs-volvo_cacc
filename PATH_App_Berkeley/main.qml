import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import QtMultimedia 5.4
import Qt.labs.settings 1.0
import FileIO 1.0
import "UDP_OUT.js" as ButtonUDPFormat

ApplicationWindow {
    id:windowRoot
    property bool isAndroid:false
    property var truckErrors:[]

    property string myTruckColor:"#4dcef3"
    property string otherTruckColor:"#a3f34d"
    property string errorTruckColor:"#ff0000"

    property string myTruckColorDarker:"#4dcef3"
    property string otherTruckColorDarker:"#a3f34d"
    property string errorTruckColorDarker:"#f34d4d"

    property string buttonColor:"#082a38"//0e3d51
    property string buttonColorDarker:"#2a7185"
    property string buttonColorLighter:"2a7185"

    property string buttonActiveColor:"#08FF2a"
    property string buttonActiveColorDarker:"#08FF2a"
    property string buttonActiveColorLighter:"08FF2a"


    property string popupColor:"#082a38"//0e3d51
    property string popupColorDarker:"#2a7185"
    property string popupColorLighter:"2a7185"

    property string fontHeadline: volvoFontBroad.name
    property string fontInstrument:volvoFontInstrument.name
    property string fontBold:volvoFontSansBold.name
    property string fontMedium:volvoFontSansMedium.name
    property int fontDefaultSize:56
    property color fontInstrumentColor:"#a2a6a7"

    property bool showInfo:false
    property int itemInfoToShow:-1
    property bool targetFound:false

    property string remoteIP:"127.0.0.1"
    property int remotePort:8002
    property var buttonUDP:ButtonUDPFormat.extraData
    property int buttonStatus:0

    property bool isLeader:udpSeret.position===0
    property int platooningState:udpSeret.platooningState
    property int popupID:udpSeret.popup
    property int numberOfTrucks:1
    property string exitDistance:(udpSeret.exitDistance/10.0).toFixed(1)
    property int myTruckID:udpSeret.position
    property var stringArray:udpSeret.vehicleArray
    property int userPopupID:0

    property bool setSpeedHasChanged:false
    property int setSpeed:udpVehicle.targetSpeed*0.621371192


    FontLoader {
        id: volvoFontBroad
        source: "fonts/VolvoBroadPro.otf"
    }

    FontLoader {
        id: volvoFontInstrument
        source: "fonts/VolvoInstrument1.otf"
    }

    FontLoader {
        id: volvoFontSansBold
        source: "fonts/VolvoSansPro-Bold.otf"
    }

    FontLoader {
        id: volvoFontSansMedium
        source: "fonts/VolvoSansPro-Medium.otf"
    }

    FileIO {
        id: myFile
        source:""
        onError: {console.log("Msg: "+msg);
            console.log("Source: "+source);
            console.log("Unable to load config. Check the following path: "+source);
        }
    }


    Timer{
        id:buttonPressTimer
        interval:200
        onTriggered:{
            buttonStatus=0
        }
    }

    Timer{
        id:sendUDPTimer
        interval:50
        running:false
        repeat:true
        onTriggered:{
            fetchAllData()
        }
    }


    Timer{
        id:setSpeedTimer
        interval: 3000
        onTriggered: {
            setSpeedHasChanged=false
        }
    }

    onSetSpeedChanged: {
        if(udpVehicle.accIcon===1 && udpVehicle.targetSpeedParanthesis===0){
            setSpeedHasChanged=true
            setSpeedTimer.restart()
        }
    }

    function fetchAllData(){
        //console.log("BTN: "+buttonStatus)
        udpSender.fetchUDPdata([buttonStatus],["quint8"],[remoteIP],8003)

    }

    onStringArrayChanged: {
        var temp=0
        for(var i=0;i<stringArray.length;i++){
            if(stringArray[i][0]>0){
                temp++;
            }
        }
        numberOfTrucks=temp;

        console.log(numberOfTrucks)
        console.log(stringArray)
//        console.log(udpXDataCACC.CACCState)
//        console.log(udpXDataCACC.ACCTimeGap)
//        console.log(udpXDataCACC.CACCTimeGap)

        truckString.recreateStringData(stringArray)
    }
    onUserPopupIDChanged: {
        if(userPopupID>0){
            userInitiatedPopup.currentPopupID=userPopupID
        }
    }

    onPopupIDChanged: {
        if(popupID>0){
            systemInitiatedPopup.currentPopupID=popupID
        }
    }

    Component.onCompleted: {
        if(Qt.platform.os==="android"){
            isAndroid=true
        }
        myTruckColorDarker=shadeColor2(myTruckColor,-0.4)
        otherTruckColorDarker =shadeColor2(otherTruckColor,-0.6)
        errorTruckColorDarker =shadeColor2(errorTruckColor,-0.6)
        buttonColorDarker =shadeColor2(buttonColor,-0.6)
        buttonColorLighter=shadeColor2(buttonColor,0.2)
        popupColorDarker =shadeColor2(popupColor,-0.6)
        popupColorLighter=shadeColor2(popupColor,0.2)
        buttonActiveColorDarker =shadeColor2(buttonActiveColor,-0.6)
        buttonActiveColorLighter=shadeColor2(buttonActiveColor,0.2)
        sendUDPTimer.start()
        remoteIP=myFile.loadIP()
        if(remoteIP===""){
            console.log("No config-file, creating and set default 127.0.0.1")
            remoteIP="127.0.0.1"
            myFile.saveIP(remoteIP)
        }

        console.log("IP to send to: "+remoteIP)
    }

    function shadeColor2(color, percent) {
        var f=parseInt(color.slice(1),16),t=percent<0?0:255,p=percent<0?percent*-1:percent,R=f>>16,G=f>>8&0x00FF,B=f&0x0000FF;
        return "#"+(0x1000000+(Math.round((t-R)*p)+R)*0x10000+(Math.round((t-G)*p)+G)*0x100+(Math.round((t-B)*p)+B)).toString(16).slice(1);
    }

    function buttonClicked(g,i){
        console.log("Group: "+g+", ID: "+i)
        if(g===0){
            //USER ACTION - trigg popup
            if(i===0){
                //Dissolve
                userPopupID=1
            }else if(i===1){
                //Leave
                userPopupID=2
            }else if(i===2){
                //Cancel operation
                userPopupID=0
            }

        }else if(g===1){
            buttonStatus=i+1
            buttonPressTimer.restart()

            userPopupID=0
        }else if(g===2){
            buttonStatus=i+5
            console.log(buttonStatus)
            buttonPressTimer.restart()
        }

    }

    function showItemInfo(i){
        console.log(i)
        if(i===itemInfoToShow){
            itemInfoToShow=-1
        }else{
            itemInfoToShow=i
        }

    }

    width:isAndroid ? 2048 : 1024// 2560 : 1280
    height:isAndroid ? 1536 : 768//1600 : 800
    visibility:isAndroid ? 5 : 2
    visible: true




    Item{
        id:scaleHolder
        scale:isAndroid ? 2 : 1
        width:1024
        height:768
        anchors.centerIn: parent

        Rectangle{
            id:mainBackground
            color:"#000000"
            anchors.fill:parent
            Image{
                id:bgSky
                source:"Images/backgroundSky.png"
                opacity:0.28
            }
            Image{
                id:bgAbstract
                source:"Images/backgroundAbstract.png"
                opacity:0.46
            }
        }

        WaitingScreen{
            id:waitingHolder

        }

        Row{
            id:buttonRow
            spacing:20
            visible:platooningState>1
            anchors.bottom:parent.bottom
            anchors.bottomMargin: 20
            anchors.left:parent.left
            anchors.leftMargin: 20
            width:240
            ButtonStandard{
                opacity:udpXDataCACC.CACCState ===2 ? 1 : 0.2
                id:joinBtn
                myID:isLeader ? 0 : 1
                myGroup:0
                btnText: isLeader ? "DISSOLVE" : "LEAVE"
            }
        }

        TruckString{
           id:truckString
           visible:platooningState>1
           anchors.horizontalCenter: buttonRow.horizontalCenter
           anchors.verticalCenter: parent.verticalCenter
           anchors.verticalCenterOffset: -70
        }

        Rectangle{
           id:delimiter01
           height:parent.height
           width:3
           anchors.left:buttonRow.right
           anchors.leftMargin: 20

           visible:platooningState>1
           color:"#0f4057"
        }
        Item{
            id:accInfoHolder
            anchors.centerIn: parent
            anchors.horizontalCenterOffset: buttonRow.width/2+20
            visible:platooningState>1 && udpXDataCACC.CACCState>0
            AccInfoCACC{
                id:accInfo
                anchors.centerIn: parent
                anchors.verticalCenterOffset: -100
            }
            Row{
                id:accButtonRow
                spacing:20
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top:accInfo.bottom
                anchors.topMargin: 20
                visible:true
                ButtonStandard{
                    id:accBtn
                    myID:0
                    myGroup:2
                    btnText: "ACC"
                    myWidth: 180
                    //myState:0
                }
                ButtonStandard{
                    id:cAccBtn
                    myID:1
                    myGroup:2
                    btnText: "CACC"
                    myWidth: 180
                    //myState:1
                }
            }
            Row{
                id:timegapButtonRow
                spacing:20
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top:accButtonRow.bottom
                anchors.topMargin: 20
                visible:true
                ButtonStandard{
                    id:timegapMinus
                    myID:2
                    myGroup:2
                    btnText: "-"
                    myWidth: 80

                }
                ButtonStandard{
                    id:timegapPlus
                    myID:3
                    myGroup:2
                    btnText: "+"
                    myWidth: 80
                }
            }
        }

        Image{
            id:setSpeedPopup
            source:"Images/PATH/CruiseSetSpeed - background-mi.png"
            anchors.bottom:parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: buttonRow.width/2+20
            opacity:setSpeedHasChanged ? 1 : 0
            visible:opacity>0
            Behavior on opacity {
                SpringAnimation{
                    damping: 1.0
                    spring: 5.0
                }
            }
            Text{
                id:accSetSpeedPopupTxt
                font.family: fontInstrument
                color:"#FFFFFF"
                font.pixelSize: 75
                width:50
                text:setSpeed//udpVehicle.targetSpeed
                anchors.left: parent.left
                anchors.leftMargin: 79
                anchors.top: parent.top
                anchors.topMargin: -4
                horizontalAlignment: Text.AlignRight
                visible:udpVehicle.accIcon===1
            }
            Image{
                id:setSpeedPopupIcon
                y: 74
                scale: 0.9
                source:"Images/PATH/Bottom Icon - ACC green-01.png"
                anchors.horizontalCenterOffset: 0
                anchors.bottom:parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter

            }
        }
    }



    FastBlur {
        id:popupBlur
        scale:isAndroid ? 2 : 1
        anchors.fill: scaleHolder
        source: scaleHolder
        radius: 32//reminderPopup.opacity*32
        opacity:popupMouseBlocker.opacity*2.5
        visible:popupMouseBlocker.visible
        cached:visible ? true : false
    }

    Item{
        id:popupHolder
        anchors.fill:parent
        scale:isAndroid ? 2 : 1

        Rectangle{
            id:popupMouseBlocker
            anchors.fill:parent
            color:"#000000"
            opacity:(userPopupID>0 || popupID>0 || platooningState===3 || platooningState===4) ? 0.4 : 0
            visible:opacity>0
            MouseArea{
                anchors.fill:parent
                onClicked:{}
                onReleased: {}
            }

            Behavior on opacity {
                SpringAnimation{
                    damping:1
                    spring:5
                }
            }
        }


        Text{
            id:leavingPopupText
            text:"Leave sequence initiated - please wait"
            color:"#FFFFFF"
            font.bold: true
            font.family: "Volvo Sans Pro"
            font.pixelSize: 40
            anchors.centerIn:parent
            anchors.verticalCenterOffset: -150
            visible:platooningState===3
        }

        Text{
            id:dissolving
            text:"Dissolving\nPlease wait for all followers to leave"
            color:"#FFFFFF"
            font.bold: true
            font.family: "Volvo Sans Pro"
            font.pixelSize: 40
            anchors.centerIn:parent
            anchors.verticalCenterOffset: -150
            horizontalAlignment: Text.AlignHCenter
            visible:platooningState===4
        }



        UserPopup{
            id:userInitiatedPopup
            opacity:userPopupID>0 ? 1:0
            scale:userPopupID>0 ? 1:1.1
        }

        Popup{
            id:systemInitiatedPopup
            opacity:popupID>0 ? 1:0
            scale:popupID>0 ? 1:1.1
        }
    }

}

