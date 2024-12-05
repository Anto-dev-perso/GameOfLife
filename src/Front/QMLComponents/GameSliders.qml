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
            imgSource: "../assets/svg/buttons/speed-gauge.svg"
            id: speedGaugeImg
            dividerRatio: 25
        }
        CustomSlider {
            id: speedGaugeSlider
            value: uiBridge._gameSpeed
            onValueChanged: uiBridge.set_gameSpeed(value)
        }
        CustomImage {
            id: gridImg
            imgSource: "../assets/svg/buttons/grid.svg"
            dividerRatio: 25
        }
        CustomSlider {
            id: gridSlider
            value: uiBridge._zoomValue
            onValueChanged: uiBridge.set_zoomValue(value)
        }
        CustomImage {
            id: nextImg
            imgSource: "../assets/svg/buttons/next_blue.svg"
            dividerRatio: 25
        }
        Text {
            text: uiBridge._iterationNumber
            color: root.gameSlidersBackgroundUnSelectedColor
        }
    }
}
