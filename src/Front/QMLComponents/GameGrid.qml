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
        Image {
            id: mainGrid
            width: parent.width
            height: parent.height

            // Call directly the Image Provider that will convert the backend grid to an Image
            source: uiBridge.getMainGridImage()
            fillMode: Image.PreserveAspectFit
        }
        Connections {
            target: uiBridge

            function on_ImageUpdated() {
                mainGrid.source = uiBridge.getMainGridImage()  // Reload the image
            }
        }
    }
}
