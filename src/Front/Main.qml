import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

import "./QMLComponents"

// TODO track all hard coded values (padding ...) to make all of these variables to the window size
ApplicationWindow {
    id: root

    width: 1400
    height: 800
    visible: true

    title: qsTr("Game of Life")

    FontLoader {
        id: customFont
        source: "assets/font/trebuchet-ms-2/trebuc.ttf"
        //source: "/assets/font/trebuchet-ms-2/Trebuchet-MS-Italic.ttf"
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

    readonly property color popUpBackgroundColor: "#38393c"
    readonly property color popUpElementBackgroundColor: "#4d4d4d"
    readonly property color popUpTextColor: "#f4f3e6"
    readonly property color popUpBorderElementColor: "#626262"

    readonly property color buttonColor: "#2a4e97"
    readonly property color buttonTextColor: "#ffffff"
    readonly property color urlLinkColor: "#91bcff"

    readonly property double topBarHeight: 0.13
    readonly property double topBarTextBottomMargin: 0.12
    readonly property double topBarTextLeftMargin: 0.02

    readonly property double bottomBarHeight: 0.2

    readonly property double gridHeight: 1 - (topBarHeight + bottomBarHeight)

    readonly property double popUpWidth: root.width / 2
    readonly property double popUpHeight: root.height * 0.9

    color: backgroundColor

    Overlay {
        id: overlay
        visible: lexiconPopUp.visible || explanationPopUp.visible
    }

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

        GameGrid {}
        GameSliders {}
    }

    GenericPopUp {
        id: lexiconPopUp
        contentOfPopUp: GenericPopUp.PopUpType.LEXICON
    }
    GenericPopUp {
        id: explanationPopUp
        contentOfPopUp: GenericPopUp.PopUpType.EXPLANATION
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
                imgSource: "../assets/svg/buttons/explanation.svg"
                onClicked: explanationPopUp.open()
            }
            ActionButton {
                buttonText: "LEXICON"
                imgSource: "../assets/svg/buttons/lexicon.svg"
                onClicked: lexiconPopUp.open()
            }
            ActionButton {
                buttonText: "START"
                imgSource: "../assets/svg/buttons/start.svg"
                onClicked: uiBridge.runGame()
            }

            ActionButton {
                buttonText: "STOP"
                imgSource: "../assets/svg/buttons/stop.svg"
                onClicked: uiBridge.stopGame()
            }
            ActionButton {
                buttonText: "NEXT"
                imgSource: "../assets/svg/buttons/next_white.svg"
                onClicked: uiBridge.runIteration()
            }

            ActionButton {
                buttonText: "RESET"
                imgSource: "../assets/svg/buttons/reset.svg"
                onClicked: uiBridge.resetPattern()
            }
            ActionButton {
                buttonText: "CLEAR"
                imgSource: "../assets/svg/buttons/clear.svg"
                onClicked: uiBridge.clearPattern()
            }
        }
    }
}
