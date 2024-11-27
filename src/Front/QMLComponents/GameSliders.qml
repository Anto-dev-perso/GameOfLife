import QtQuick
import QtQuick.Controls

Rectangle {
    id: gameSliders


    anchors {
        bottom: parent.bottom
        right: parent.right
        bottomMargin: root.gameSlidersMargins
        rightMargin: root.gameSlidersMargins
    }
    radius: 10

    color: root.gameSlidersColor

    implicitWidth: slidersLayout.implicitWidth + 50
    implicitHeight: slidersLayout.implicitHeight + 50

    Grid {
        id: slidersLayout
        anchors.centerIn: parent

        columns: 2
        rowSpacing: 15
        columnSpacing: 10
        padding: 10

        CustomImage {
            imgSource: "../assets/svg/speed-gauge.svg"
            id: speedGaugeImg
        }
        CustomSlider {
            id: speedGaugeSlider
            value: uiBridge._gameSpeed
            onValueChanged: uiBridge.set_gameSpeed(value)
        }
        CustomImage {
            imgSource: "../assets/svg/grid.svg"
            id: gridImg
        }
        CustomSlider {
            id: gridSlider
            value: uiBridge._mainGridModel._zoomValue
            onValueChanged: uiBridge._mainGridModel.set_zoomValue(value)
        }
        CustomImage {
            imgSource: "../assets/svg/next_blue.svg"
            id: nextImg
        }
        Text {
            text: uiBridge._iterationNumber
            color: root.gameSlidersBackgroundUnSelectedColor
        }
    }
}
