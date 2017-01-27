import QtQuick 2.5

Row{
    property string starSource:"Images/ratingStar.png"
    property string strokeSource:"Images/ratingStarStroke.png"
    property int myRating:3

    spacing:3
    Repeater{
        model:5
        Image{
            source:index < myRating ? starSource : strokeSource
        }
    }

}

