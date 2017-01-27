import QtQuick 2.3

import QtGraphicalEffects 1.0

Item{
    id:accInfo
    height:400
    width:400
    property real hwCruiseRatio:udpXData.hwCruiseRatio/100.0
    property bool targetDetected:udpVehicle.accTarget
    property real ccEnabladOpacityLevel:0.2

    property real lkaLimit1:0.3
    property real lkaLimit2:0.5
    property real lkaLimit3:0.8
    property real lkaLimit4:0.99

    property bool cruiseChangedActive:false
    property int cruiseChangedValue:0

    Item{
        id:cruiseIcon
        anchors.centerIn:parent
        anchors.horizontalCenterOffset:-6
        visible:udpVehicle.accIcon>0
        Image{
            id:ccLanes
            anchors.centerIn:parent
            opacity:hwCruiseRatio>=lkaLimit4 ? (udpVehicle.targetSpeedParanthesis===0 ? 1 : ccEnabladOpacityLevel) :ccEnabladOpacityLevel
            source:udpXData.autoPilotState===0 ? "Images/Cruise/ccLanesGrey.png" : "Images/Cruise/ccLanesBlue.png"
        }

        Image{
            id:lkaLevel1Image
            anchors.centerIn: parent
            anchors.verticalCenterOffset: 48
            source:udpXData.autoPilotState===0 ?"Images/Cruise/LKA_Level1.png" : "Images/Cruise/LKA_Level1Blue.png"
            opacity:hwCruiseRatio>lkaLimit1  ? (udpVehicle.targetSpeedParanthesis===0 ? 1 : 0) :0
            visible:opacity>0
            Behavior on opacity{
                SpringAnimation{
                    damping: 1
                    spring:5
                }
            }

        }
        Image{
            id:lkaLevel2Image
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -18
            source:udpXData.autoPilotState===0 ?"Images/Cruise/LKA_Level2.png":"Images/Cruise/LKA_Level2Blue.png"
            opacity:hwCruiseRatio>=lkaLimit2 ? (udpVehicle.targetSpeedParanthesis===0 ? 1 : 0) :0
            visible:opacity>0
            Behavior on opacity{
                SpringAnimation{
                    damping: 1
                    spring:5
                }
            }

        }
        Image{
            id:lkaLevel3Image
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -62
            source:udpXData.autoPilotState===0 ?"Images/Cruise/LKA_Level3.png":"Images/Cruise/LKA_Level3Blue.png"
            opacity:hwCruiseRatio>=lkaLimit3  ? (udpVehicle.targetSpeedParanthesis===0 ? 1 : 0) :0
            visible:opacity>0
            Behavior on opacity{
                SpringAnimation{
                    damping: 1
                    spring:5
                }
            }

        }


        Image{
            id:ccGap
            anchors.centerIn:parent
            anchors.verticalCenterOffset: 30
            opacity:udpVehicle.accIcon>0 && udpVehicle.accIcon<5 &&udpVehicle.targetSpeedParanthesis===0 ? 1 : ccEnabladOpacityLevel
            source:udpXData.autoPilotState===0 ? "Images/Cruise/ccGapGrey.png" : "Images/Cruise/ccGapBlue.png"

        }
        Image{
            id:ccTarget
            anchors.centerIn:parent
            anchors.verticalCenterOffset: -35
            source:udpXData.autoPilotState===0 ? "Images/Cruise/ccTargetGrey.png" :"Images/Cruise/ccTargetBlue.png"
            visible:(udpVehicle.accTarget>0 && udpVehicle.accIcon>0 && udpVehicle.accIcon<5) ? true:false
            opacity:(udpVehicle.targetSpeedParanthesis===0 ? 1 : ccEnabladOpacityLevel)
        }
        Item{
            id:ccWifiContainer
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -70
            visible:false
            Image{
                id:ccWifiDot
                anchors.centerIn:parent
                source:udpXData.autoPilotState===0 ? "Images/Cruise/ccWifiDotGrey.png" :"Images/Cruise/ccWifiDotBlue.png"
            }
            Image{
                id:ccWifi
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom:ccWifiDot.top
                anchors.bottomMargin:0
                source:udpXData.autoPilotState===0 ? "Images/Cruise/ccWifiGrey.png" :"Images/Cruise/ccWifiBlue.png"
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
                font.family: volvoFontSansMedium.name
                font.pointSize: isAndroid ? 24 : 30
                text:udpXData.autoPilotState===0 ?  accText : udpXData.autoPilotMode===0 ? functionNameQueueCap :functionNameHWCap
                horizontalAlignment: Text.AlignHCenter
                anchors.centerIn: parent
                opacity:udpVehicle.accIcon>0 && udpVehicle.accIcon<5 && udpVehicle.targetSpeedParanthesis===0 ? 1 : ccEnabladOpacityLevel
                color:udpXData.autoPilotState===0 ? fontInstrumentColor : "#007dc8"
            }

        }

        Rectangle{
            id:cruiseChangedPopup
            radius:10
            width:350
            height:80
            border.width: 4
            border.color: "#494e52"
            color:"#373e42"
            visible:opacity>0
            opacity:cruiseChangedActive ? 1:0
            scale:cruiseChangedActive ? 1:0.9
            anchors.top:apIconActive.bottom
            anchors.topMargin:20
            anchors.horizontalCenter: parent.horizontalCenter
            Behavior on opacity{
                SpringAnimation{
                    damping: 1
                    spring:5
                }
            }
            Behavior on scale{
                SpringAnimation{
                    damping: 1
                    spring:5
                }
            }

            Image{
                id:arrow1
                source:"Images/Clinic/accChangePopupArrowRight.png"
                anchors.left:ccTxt.right
                anchors.leftMargin:25
                anchors.verticalCenter: parent.verticalCenter
            }

            Image{
                id:arrow2
                source:"Images/Clinic/accChangePopupArrowLeft.png"
                anchors.left:ccTxt.right
                anchors.leftMargin:5
                anchors.verticalCenter: parent.verticalCenter
                visible: udpXData.armedState!==1
            }

            Image{
                id:arrow3
                source:"Images/Clinic/accChangePopupArrowRight.png"
                anchors.left:accTxt.right
                anchors.leftMargin:10
                anchors.verticalCenter: parent.verticalCenter
                visible: udpXData.armedState===1

            }

            Text{
                id:ccTxt
                font.family: volvoFontSansMedium.name
                font.pointSize: 30
                text:"CC"
                //horizontalAlignment: Text.AlignHCenter
                anchors.left: parent.left
                anchors.leftMargin:10
                anchors.verticalCenter: parent.verticalCenter
                opacity:cruiseChangedValue===0 ? 1:ccEnabladOpacityLevel
                color:fontInstrumentColor

            }

            Text{
                id:accTxt
                font.family: volvoFontSansMedium.name
                font.pointSize: 30
                text:"ACC"
                anchors.centerIn: parent
                opacity:cruiseChangedValue===1 ? 1:ccEnabladOpacityLevel
                color:fontInstrumentColor
            }

            Image{
                id:daImage
                source:"Images/Clinic/accChangePopupWheel.png"
                smooth:true
                anchors.right: parent.right
                anchors.rightMargin:10
                anchors.verticalCenter: parent.verticalCenter
                opacity:cruiseChangedValue===2 ? 1:ccEnabladOpacityLevel
                //visible:udpXData.armedState===1
            }
        }

        Image{
            id:apIconAvailable
            source:"Images/Clinic/iconApAvailable.png"
            opacity: apAvailableState  ? ccEnabladOpacityLevel : 0
            visible:opacity>0
            anchors.top:accStateTextHolder.bottom
            anchors.topMargin:5
            anchors.horizontalCenter: parent.horizontalCenter

            Behavior on opacity{
                SpringAnimation{
                    damping: 1
                    spring:5
                }
            }
        }

        Image{
            id:apIconArmed
            source:"Images/Clinic/iconAPArmed.png"
            opacity: apArmedState  ? 1 : 0
            visible:opacity>0
            anchors.top:accStateTextHolder.bottom
            anchors.topMargin:5
            anchors.horizontalCenter: parent.horizontalCenter

            Behavior on opacity{
                SpringAnimation{
                    damping: 1
                    spring:5
                }
            }
        }

        Image{
            id:apIconActive
            source:"Images/Clinic/iconAPActive.png"
            opacity: udpXData.autoPilotState>0  ? 1 : 0
            visible:opacity>0
            anchors.top:accStateTextHolder.bottom
            anchors.topMargin:5
            anchors.horizontalCenter: parent.horizontalCenter

            Behavior on opacity{
                SpringAnimation{
                    damping: 1
                    spring:5
                }
            }
        }

        Image{
            id:apIconHandsNeeded
            source:"Images/Clinic/iconHandsHeadsUp.png"
            opacity: udpXData.autoPilotState===2  ? 1 : 0
            visible:opacity>0
            anchors.top:accStateTextHolder.bottom
            anchors.topMargin:5
            anchors.horizontalCenter: parent.horizontalCenter

            Behavior on opacity{
                SpringAnimation{
                    damping: 1
                    spring:5
                }
            }
        }
    }
}
