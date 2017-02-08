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

    property string buttonColor:"#3292ba"   //0e3d51 #082a38
    property string buttonColorDarker:"#2a7185"
    property string buttonColorLighter:"2a7185"

    property string buttonActiveColor:"#08FF2a"
    property string buttonActiveColorDarker:"#08FF2a"
    property string buttonActiveColorLighter:"08FF2a"


    property string popupColor:"#082a38"  //0e3d51
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
    property int numberOfTrucks:1   // SY: The default is 1
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
        console.log("Group: "+g+", ID: "+i) // print debugging information to the console
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


    property alias timegapPlus: timegapPlus
    property alias timegapMinus: timegapMinus
    property alias truckString: truckString
    property alias cAccBtn: cAccBtn
   // property alias popupMouseBlocker: popupMouseBlocker
    property alias timegapButtonColumn: timegapButtonColumn
    property alias buttonRow: buttonRow

    width:isAndroid ?2048:1024//1600 : 800
    height:isAndroid ?1536:768
    visibility:isAndroid ? 5 : 2
    visible: true




    Item{
        id:scaleHolder
                scale:isAndroid ? 2 : 1
                width:1024
                height:768
                anchors.verticalCenterOffset: -6
                anchors.horizontalCenterOffset: 0
                anchors.centerIn: parent

        Rectangle{
            id:mainBackground
            color:"#000000"
            anchors.rightMargin: 0
            anchors.bottomMargin: -12
            anchors.leftMargin: 1
            anchors.topMargin: 0
            anchors.fill:parent
            Image{
                id:bgAbstract
                x: 0
                y: 5
                width: 1383
                height: 831
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

        }



        TruckString{
            id:truckString
            width: 156
            height: 580
            anchors.horizontalCenterOffset: -6

           anchors.verticalCenterOffset: 0

           anchors.horizontalCenter: buttonRow.horizontalCenter
           anchors.verticalCenter: parent.verticalCenter
           visible:platooningState>1
          }

        Rectangle{
           id:delimiter01

           height:parent.height
           width:3
           anchors.left:buttonRow.right
           anchors.leftMargin: 6
           visible:platooningState>1
           color:"#0f4057"
        }




  Item{
            id:accInfoHolder
            anchors.centerIn: parent
            anchors.horizontalCenterOffset: buttonRow.width/2+20
            visible: platooningState>1 && udpXDataCACC.CACCState>0


            AccInfoCACC{
                id:accInfo
                x:0
                y:0
                width: 551//398  // which is to control the blue window
                height: 385//102 // which is to control the blue window
                anchors.verticalCenterOffset: -62
                anchors.horizontalCenterOffset: 52
                scale: 1
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter

            }
            Row{
                id:accButtonRow
                x: -300
                y: 188
                width: 520
                height: 110
                anchors.horizontalCenterOffset: 51
                layoutDirection: Qt.LeftToRight
                anchors.horizontalCenter: parent.horizontalCenter
                spacing:75

                visible:true

                ButtonStandard{
                    id:cAccBtn
                    x: -148
                    y: 14
                    width: 225
                    height: 100
                    clip: false
                    anchors.margins: 2

                    myID:1
                    myGroup:2
                    btnText: "CACC"
                    myHeight: 80
                    myWidth: 225// SY: Change the parameters from 180 to 225
                    //myState:1
                }
                ButtonStandard{
                    id:accBtn
                    x: 144
                    y: 14
                    width: 225
                    height: 100
                    anchors.margins: 2

                    myID:0
                    myGroup:2
                    btnText: "ACC"
                    myHeight: 80
                    myWidth: 225  // SY: Change the parameters from 180 to 225
                    //myState:0
                }

            }

            Column{
                id:timegapButtonColumn
                x: -200
                y: 300
                width: 117
                height: 326
                anchors.verticalCenterOffset: -62
                anchors.horizontalCenterOffset: -226
                smooth: true
                enabled: true
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter

                spacing:80
                visible:true

                ButtonStandard2{
                    id:timegapPlus
                    width: 120
                    height: 120
                    scale: 1

                    myID:3
                    myGroup:2
                    btnText:"⇧" // SY: this "⬆" is backup
                    myWidth: 110 // SY: change the button size from 80 to 110
                    myHeight: 110
                }

                ButtonStandard2{
                    id:timegapMinus
                    width: 120
                    height: 120
                    scale: 1

                    btnText: "⇩" //SY: this "⬇" is backup
                    myID:2
                    myGroup:2
                    myWidth: 110 // SY: change the parameters from 80 to 110
                    myHeight: 110
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



  /*  FastBlur {
        id:popupBlur
        scale:isAndroid ? 2 : 1
        anchors.fill: scaleHolder
        source: scaleHolder
        radius: 32
        anchors.bottomMargin: 12
        anchors.leftMargin: 8
        anchors.topMargin: -12
        anchors.rightMargin: -8//reminderPopup.opacity*32
        opacity:popupMouseBlocker.opacity*2.5
        visible:popupMouseBlocker.visible
        cached:visible ? true : false
    }

  Item{
        id:popupHolder
        visible: false
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
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
*/
}

