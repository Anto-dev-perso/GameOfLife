import QtQuick

Rectangle {
    id: grid

    anchors.centerIn: parent

    width: parent.width - root.gameSlidersMargins
    height: parent.height - root.gameSlidersMargins

    Grid {
        anchors.fill: parent

        columns: gridData._UIColumnCount
        rows: gridData._UILineCount

        Repeater {
            model: gridData

            Rectangle {
                width: parent.width / parent.columns
                height: parent.height / parent.rows
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
        }
    }
}
