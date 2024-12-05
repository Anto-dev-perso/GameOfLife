import QtQuick

Loader {

    sourceComponent: Rectangle {
        id: overlay

        anchors.fill: parent
        color: root.gridBackgroundColor
        opacity: 0.9
        z: 1
    }
}
