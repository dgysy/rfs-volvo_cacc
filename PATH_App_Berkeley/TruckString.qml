import QtQuick 2.5
import QtGraphicalEffects 1.0


Item {
    id:truckStringRoot
    width:130
    height:(stringRow.truckHeight+stringRow.spacing)*numberOfTrucks + 80

  // This is the code we need to control the car icon.
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

            /*if(newData[i][3]>0){
                temp.isTemporaryLeader=true
            }else{
                temp.isTemporaryLeader=false
            }*/

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
        color:"transparent" // udpXDataCACC.CACCState===2? "#FFFFFF" :"transparent"  if CACC on, show white line; if off, disable line
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
       // width: 114
       // height: 184 //the width and height will change the position
                      // relative to the left and right lines

        anchors.centerIn: stringLine
        Behavior on height{
            SpringAnimation{
                damping:1
                spring:5
            }
        }

        spacing: 120 //SY3: the space between trucks were changed

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
                        if(index===0){ // the tuck is in a leader postion
                            if(index===myTruckID){
                                if(udpXDataCACC.CACCState===2){ // here means when CACC is active
                                    return("#5ea6f5") // SY:the leading truck is always blue "#008cff"
                                }/*else{
                                    return("#31FF06")
                                }*/
                            }else{
                                return("#00000000")
                            }
                        }/*else if (index===myTruckID){
                            return("#31FF06")  // SY: remove the redundant color green
                        }*/else{
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
                        width:65//47 SY3: the width was changed
                        radius:8
                        height:160//113 SY3: the height was changed
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
                        source:"Images/PATH/vehLeader.png"
                        scale: 1.4 // SY:  enlarge the truck icon

                       // source:calculateImagesource()

                        // My Turck ID is 0 (leading truck), 1 (following), 2(following)
                       /* function calculateImagesource(){
                            if(index===myTruckID){
                               return("Images/PATH/vehEgo.png")
                            }else if(index===0 && udpXDataCACC.CACCState===2){
                               return("Images/PATH/vehLeader.png")
                            }else{
                                return("Images/PATH/vehFollower.png")
                            }
                         }*/
                    }


                    // SY3: A pair of Green Triangles to indicate the truck where driver at.
                    Image{
                         id:dringTruck
                        anchors.centerIn: parent
                        source:"Images/PATH/greenTri2.png"
                        visible:modelData.ID===myTruckID // SY3: what does myTruckID mean?
                        scale: 1.4
                        }


                    Image{
                        id:badComIcon
                        anchors.centerIn: parent
                        anchors.verticalCenterOffset: 10// default is 30
                        source:"Images/PATH/badCom.png"
                        scale:1.5
                        visible:modelData.Type===2 // 2=truck with communication error
                    }

                }
            }
        }
    }
}

