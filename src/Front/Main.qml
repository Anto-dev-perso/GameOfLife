import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

import "./QMLComponents"

import UIBridge

// TODO track all hard coded values (padding ...) to make all of these variables to the window size
Window {
    id: root

    width: 1400
    height: 800
    visible: true

    title: qsTr("Game of Life")

    FontLoader {
        id: customFont
        source: "assets/font/trebuchet-ms-2/trebuc.ttf"
        //source: "../assets/font/trebuchet-ms-2/Trebuchet-MS-Italic.ttf"
    }

    readonly property color bandColor: "#3663a8"
    readonly property color bandTextColor: "#aacbff"
    readonly property color backgroundColor: "#646464"

    readonly property color gridBackgroundColor: "#404040"
    readonly property color gridBorderColor: "#989898"
    readonly property color cellDeadColor: "#7e7e7e"
    readonly property color cellAliveColor: "#ffff00"

    readonly property color gameSlidersColor: "#6c6c6c"
    readonly property int gameSlidersMargins: 20
    readonly property color gameSlidersBackgroundSelectedColor: "#2a4e97"
    readonly property color gameSlidersBackgroundUnSelectedColor: "#efefef"
    readonly property color gameSlidersHandleColor: gameSlidersBackgroundSelectedColor

    readonly property color buttonColor: "#2a4e97"
    readonly property color buttonTextColor: "#ffffff"

    readonly property double topBarHeight: 0.13
    readonly property double topBarTextBottomMargin: 0.12
    readonly property double topBarTextLeftMargin: 0.02

    readonly property double bottomBarHeight: 0.2

    readonly property double gridHeight: 1 - (topBarHeight + bottomBarHeight)

    UIBridge {
        id: uiBridge
    }

    color: backgroundColor

    Rectangle {
        id: topBar

        width: parent.width
        height: parent.height * topBarHeight

        anchors.top: parent.top

        color: root.bandColor

        Text {
            text: "Conway's Game of Life"

            font {
                pixelSize: 40
                family: customFont.name
            }
            color: bandTextColor

            anchors {
                bottom: parent.bottom
                left: parent.left
                bottomMargin: parent.height * topBarTextBottomMargin
                leftMargin: parent.width * topBarTextLeftMargin
            }
            opacity: 0.9
        }
    }

    Rectangle {
        id: gridLayout

        width: parent.width
        height: parent.height * gridHeight

        anchors.top: topBar.bottom

        color: root.gridBackgroundColor

        GameGrid {
        }
        GameSliders {
        }
    }

    Rectangle {
        id: bottomBar

        width: parent.width
        height: parent.height * bottomBarHeight

        anchors.bottom: parent.bottom

        color: root.backgroundColor

        Row {
            anchors.centerIn: parent
            spacing: 30

            ActionButton {
                buttonText: "EXPLANATION"
                imgSource: "../assets/svg/explanation.svg"
            }
            ActionButton {
                buttonText: "LEXICON"
                imgSource: "../assets/svg/lexicon.svg"
            }
            ActionButton {
                buttonText: "START"
                imgSource: "../assets/svg/start.svg"
                textSize: 24
                onClicked: uiBridge.runGame()
            }

            ActionButton {
                buttonText: "STOP"
                imgSource: "../assets/svg/stop.svg"
                textSize: 24
                onClicked: uiBridge.stopGame()
            }
            ActionButton {
                buttonText: "NEXT"
                imgSource: "../assets/svg/next_white.svg"
                onClicked: uiBridge.runIteration()
            }

            ActionButton {
                buttonText: "RESET"
                imgSource: "../assets/svg/reset.svg"
            }
            ActionButton {
                buttonText: "CLEAR"
                imgSource: "../assets/svg/clear.svg"
            }
        }
    }
}
