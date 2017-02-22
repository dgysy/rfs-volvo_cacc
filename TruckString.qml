import QtQuick 2.5
import QtGraphicalEffects 1.0


Item {
    id:truckStringRoot
    width:130
    height:(stringRow.truckHeight+stringRow.spacing)*numberOfTrucks + 80

    property var stringData:[
        {"ID":0,"Type":0,"Destination":"","Intruder":false,"isTemporaryLeader":false,"isBraking":false},
        {"ID":1,"Type":0,"Destination":"","Intruder":false,"isTemporaryLeader":false,"isBraking":false},
        {"ID":2,"Type":0,"Destination":"","Intruder":false,"isTemporaryLeader":false,"isBraking":false}
    ]


    function recreateStringData(newData){
        var items=[]
        var temp={}
        var hej={}

        for(var i=0;i<numberOfTrucks;i++){

            temp={}
            temp.ID=i
            temp.Type=newData[i][0]
            if(newData[i][1]>0){
                temp.Intruder=true
            }else{
                temp.Intruder=false
            }
            temp.IsBraking=newData[i][2]

            if(newData[i][3]>0){
                temp.isTemporaryLeader=true
            }else{
                temp.isTemporaryLeader=false
            }

            temp.Destination=""
            items.push(temp)
        }
        stringData=items
    }



    Gradient{
        id:errorTruckGradient
        GradientStop { position: 0; color: errorTruckColorDarker }
        GradientStop { position: 0.33; color: errorTruckColor }
        GradientStop { position: 1; color: errorTruckColorDarker }

    }


   Gradient{
        id:roadBGGradiant
        GradientStop { position: 0.0; color: "#00000000" }
        GradientStop { position: 0.1; color: "#55000000" }
        GradientStop { position: 0.9; color: "#55000000" }
        GradientStop { position: 1; color: "#00000000" }

    }

    Gradient{
        id:roadLineGradient
        GradientStop { position: 0.0; color: "#00FFFFFF" }
        GradientStop { position: 0.1; color: "#FFFFFFFF" }
        GradientStop { position: 0.9; color: "#FFFFFFFF" }
        GradientStop { position: 1; color: "#00FFFFFF" }

    }



    Rectangle{
        id:bgBox
        width:parent.width
        height:(stringRow.truckHeight+stringRow.spacing)*numberOfTrucks + 80
        color:"#000000"
        gradient: roadBGGradiant
        anchors.centerIn: parent
        Behavior on height{
            SpringAnimation{
                damping:1
                spring:5
            }
        }
    }

    Rectangle{
        id:leftLine
        width:6
        gradient: roadLineGradient
        anchors.verticalCenter: parent.verticalCenter
        anchors.left:parent.left
        height:(stringRow.truckHeight+stringRow.spacing)*numberOfTrucks + 80
        Behavior on height{
            SpringAnimation{
                damping:1
                spring:5
            }
        }

    }

    Rectangle{
        id:rightLine
        width:6
        gradient: roadLineGradient
        anchors.verticalCenter: parent.verticalCenter
        anchors.right:parent.right
        height:(stringRow.truckHeight+stringRow.spacing)*numberOfTrucks + 80
        Behavior on height{
            SpringAnimation{
                damping:1
                spring:5
            }
        }
    }



   Rectangle{
        id:stringLine
        width:8
        radius:8
        border.width:0
        color:"transparent" //disable string line perceptually
        anchors.centerIn: parent
        height:(stringRow.truckHeight+stringRow.spacing)*numberOfTrucks + 20
        Behavior on height{
            SpringAnimation{
                damping:1
                spring:5
            }
        }
    }




    Column{
        id:stringRow
        property int truckHeight:70

        anchors.centerIn: stringLine
        Behavior on height{
            SpringAnimation{
                damping:1
                spring:5
            }
        }

        spacing: 80
        Repeater{
            model:stringData
            Item{
                width:50
                height:stringRow.truckHeight+10
                anchors.horizontalCenter: stringRow.horizontalCenter

                Rectangle{
                    id:intruder
                    width:26
                    height:modelData.Intruder ? 26 : 0
                    visible:modelData.Intruder
                    radius:width/2
                    gradient:errorTruckGradient
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom:myBack.top
                    anchors.bottomMargin:12
                    border.width:2
                    border.color:errorTruckColor
                }

                Rectangle{     //SY: I guess here myBack means the background
                    id:myBack
                    opacity:1
                    width:47
                    radius:8
                    height:113
                    anchors.centerIn: parent
                    visible:index<numberOfTrucks
                    color:calculateMyColor()

                    function calculateMyColor(){
                        if(index===0){
                            if(index===myTruckID){
                                if(udpXDataCACC.CACCState===2){
                                    return("#008cff")
                                }else{
                                    return("#31FF06")
                                }
                            }else{
                                return("#00000000")
                            }
                        }else if(modelData.isTemporaryLeader){
                            return ("#008cff")
                        }else if (index===myTruckID){
                            return("#31FF06")
                        }else{
                            return("#00000000")
                        }
                    }

                    Rectangle{
                        id:vehicleStraightEnd
                        width:47
                        color:parent.color
                        height:10
                        anchors.bottom:parent.bottom

                    }

                    Rectangle{
                        id:brakingColor
                        width:47
                        radius:8
                        height:113
                        anchors.centerIn: parent
                        visible:modelData.IsBraking>0
                        color:modelData.IsBraking=== 2 ? "#FF0000" : "#FF0000"

                        Rectangle{
                            id:brakingColorEnd
                            width:47
                            color:parent.color
                            height:10
                            anchors.bottom:parent.bottom

                        }
                    }

                    Image{
                        id:vehImage
                        anchors.centerIn: parent
                        source:calculateImagesource()
                        function calculateImagesource(){
                            if(index===myTruckID){
                               return("Images/PATH/vehEgo.png")
                            }else if(index===0 && udpXDataCACC.CACCState===2){
                               return("Images/PATH/vehLeader.png")
                            }else{
                                return("Images/PATH/vehFollower.png")
                            }
                         }
                     }
                    Image{
                        id:badComIcon
                        anchors.centerIn: parent
                        anchors.verticalCenterOffset: 30
                        source:"Images/PATH/badCom.png"
                        visible:modelData.Type===2
                    }

                }
            }
        }
    }
}

