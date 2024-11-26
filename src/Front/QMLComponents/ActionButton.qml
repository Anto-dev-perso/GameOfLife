import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

Button {

    property string buttonText

    property int textSize: 18

    property url imgSource
    property int imgSize: textSize
    property int imgWidth: imgSize
    property int imgHeight: imgSize

    property color defaultColor: root.buttonColor
    property color pressedColor: Qt.darker(defaultColor, 1.1)

    id: actionButton

    background: Rectangle {
        id: actionButtonBackground

        color: actionButton.pressed ? pressedColor : defaultColor
        border {
            width: 3
            color: root.buttonColor
        }

        radius: 20

        anchors.fill: parent
    }
    transitions: [
        Transition {
            NumberAnimation {
                properties: "verticalCenterOffset, color"
                duration: 200
            }
        }
    ]

    implicitWidth: contentItem.implicitWidth
    implicitHeight: contentItem.implicitHeight

    contentItem: Row {
        id: buttonContent
        spacing: 10

        bottomPadding: 15
        topPadding: 10
        rightPadding: 30
        leftPadding: 30

        anchors {
            centerIn: parent
            verticalCenterOffset: actionButton.pressed ? 1 : 0
        }

        Image {
            source: actionButton.imgSource
            width: actionButton.imgWidth
            height: actionButton.imgHeight
            visible: imgSource !== ""
            smooth: true
        }

        Text {
            text: actionButton.buttonText
            font {
                pixelSize: actionButton.textSize
                family: customFont.name
            }
            color: root.buttonTextColor
        }
        transitions: [
            Transition {
                NumberAnimation {
                    properties: "anchors.verticalCenterOffset"
                    duration: 100
                }
            }
        ]
    }


}
