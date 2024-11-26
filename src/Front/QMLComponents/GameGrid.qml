import QtQuick
import UIBridge

Rectangle {
    id: rootGrid

    anchors.centerIn: parent
    clip: true

    width: parent.width - root.gameSlidersMargins
    height: parent.height - root.gameSlidersMargins
    Item {
        id: zoomItem
        anchors.fill: parent

        // TODO run profiler because perfo issues at scale min
        scale: uiBridge._scaleFactor
        transformOrigin: Item.Center

        GridView {
            id: qtGrid
            anchors.centerIn: parent

            width: parent.width
            height: parent.height

            model: uiBridge

            cellHeight: (qtGrid.height / uiBridge._UILineCount)
            cellWidth: (qtGrid.width / uiBridge._UIColumnCount)
            cacheBuffer: Math.max(200, uiBridge._zoomValue * 20)

            delegate: Rectangle {
                width: qtGrid.cellWidth
                height: qtGrid.cellHeight

                layer {
                    smooth: true
                    enabled: true
                }

                color: model.value ? root.cellAliveColor : root.cellDeadColor
                border {
                    width: 1
                    color: root.gridBorderColor
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        model.value = !model.value
                    }
                }
            }
            Behavior on scale {

                NumberAnimation {

                    duration: 300
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }
}
