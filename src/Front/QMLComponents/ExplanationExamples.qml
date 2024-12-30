import QtQuick

Item {
    id: explanationExample

    required property url imgLeftSource
    required property url imgRightSource

    Row {
        anchors.fill: parent
        CustomImage {
            width: explanationExample.width / 3
            height: explanationExample.height
            imgSource: imgLeftSource
        }
        CustomImage {
            anchors.verticalCenter: parent.verticalCenter
            width: explanationExample.width / 3
            height: explanationExample.height / 2
            imgSource: "../assets/svg/buttons/next_white.svg"
            dividerRatio: 2
        }
        CustomImage {
            width: explanationExample.width / 3
            height: explanationExample.height
            imgSource: imgRightSource
        }
    }
}
