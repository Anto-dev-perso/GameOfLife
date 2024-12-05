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
    property int paddingLeft: 0
    property int paddingTop: 0
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

    implicitWidth: (contentItem.implicitWidth + contentItem.spacing + contentItem.rightPadding + contentItem.leftPadding)
    implicitHeight: (contentItem.implicitHeight + contentItem.spacing + contentItem.bottomPadding + contentItem.topPadding)

    contentItem: Row {
        id: buttonContent
        spacing: 10

        bottomPadding: 7
        topPadding: actionButton.paddingTop
        rightPadding: 12
        leftPadding: actionButton.paddingLeft

        anchors {
            centerIn: parent
            verticalCenterOffset: actionButton.pressed ? 1 : 0
        }


        CustomImage {
            id: buttonImage
            imgSource: actionButton.imgSource
            dividerRatio: 25

        }

        Text {
            id: buttonText
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
