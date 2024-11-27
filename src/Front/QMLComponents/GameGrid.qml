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
        scale: uiBridge._mainGridModel._scaleFactor
        transformOrigin: Item.Center

        GridView {
            id: mainGrid
            anchors.centerIn: parent

            width: parent.width
            height: parent.height

            interactive: false

            model: uiBridge._mainGridModel

            cellHeight: (mainGrid.height / model._UILineCount)
            cellWidth: (mainGrid.width / model._UIColumnCount)

            delegate: Rectangle {

                width: mainGrid.cellWidth
                height: mainGrid.cellHeight

                layer {
                    smooth: true
                    enabled: true
                }
                color: model.cellValue ? root.cellAliveColor : root.cellDeadColor


                border {
                    width: 1
                    color: root.gridBorderColor
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        model.cellValue = !model.cellValue
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
