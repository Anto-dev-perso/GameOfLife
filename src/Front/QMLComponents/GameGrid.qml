import QtQuick

Rectangle {
    id: rootGrid

    anchors.centerIn: parent
    clip: true

    width: parent.width - root.gameSlidersMargins
    height: parent.height - root.gameSlidersMargins

    Item {
        id: zoomItem
        anchors.fill: parent

        scale: uiBridge._scaleFactor
        transformOrigin: Item.Center
        Image { // TODO customImage ?
            id: mainGrid
            anchors.fill: parent

            // Call directly the Image Provider that will convert the backend grid to an Image
            source: uiBridge.getMainGridImage()
            MouseArea {
                anchors.fill: parent
                onClicked: uiBridge.editCellOnPosition(mouseX, mouseY, width, height)
            }
        }
        Connections {
            target: uiBridge

            function on_ImageUpdated() {
                mainGrid.source = uiBridge.getMainGridImage()  // Reload the image
            }
        }
    }
}
