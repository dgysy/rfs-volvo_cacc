import QtQuick 2.5
import QtGraphicalEffects 1.0


Item {
    id:infoString
    width:240
    height:(stringRow.truckHeight+20)*numberOfTrucks + 80

    Rectangle{
        id:infoStringLine
        width:8
        radius:8
        border.width:2
        color:"#FFFFFF"
        anchors.centerIn: parent
        height:(stringRow.truckHeight+20)*numberOfTrucks + 20
        Behavior on height{
            SpringAnimation{
                damping:1
                spring:5
            }
        }
    }

    Column{
        id:stringRow
        property int truckHeight:60
        anchors.centerIn: infoStringLine
        anchors.verticalCenterOffset: 30
//        Behavior on height{
//            SpringAnimation{
//                damping:1
//                spring:5
//            }
//        }

        spacing: 20
        Repeater{
            model:numberOfTrucks
            Item{
                height:modelData<3 ? index=== myTruckID ? stringRow.truckHeight+10 : stringRow.truckHeight : 20
                width:240
                Rectangle{
                    id:myBack
                    opacity:1
                    width:240
                    radius:height/3
                    height:6
                    border.width: 2
                    border.color: "#000000"
                    color:"#FFFFFF"
                    //anchors.right:stringRow.horizontalCenter
                    //gradient: modelData<3 ? index===myTruckID ? myTruckGradient : otherTruckGradient : errorTruckGradient
                    //color:index===myTruckID ? myTruckColorDarker : otherTruckColorDarker
                    visible:index<numberOfTrucks


                }
                Behavior on height{
                    SpringAnimation{
                        damping:1
                        spring:5
                    }
                }
                Behavior on width{
                    SpringAnimation{
                        damping:1
                        spring:5
                    }
                }
            }

        }
    }

}

