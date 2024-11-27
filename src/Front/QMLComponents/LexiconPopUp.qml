import QtQuick
import QtQuick.Controls


Popup {
    id: genericPopUp
    modal: true
    focus: true


    width: popUpWidth
    height: popUpHeight
    anchors.centerIn: parent

    contentItem: ScrollView {
        id: popUpScroll
        anchors.fill: parent


        ListView {
            id: popUpListView
            spacing: genericPopUp.height / 20
            model: uiBridge._lexiconNameModel
            cacheBuffer: currentItem.implicitHeight * 40
            clip: true
            delegate: Rectangle {
                id: rootPatternElement

                width: popUpListView.width - popUpListView.spacing
                implicitHeight: 50 + lexiconElement.implicitHeight

                radius: popUpListView.spacing / 10
                property int patternIndex: index

                anchors.horizontalCenter: parent.horizontalCenter

                color: root.popUpElementBackgroundColor
                border.color: popUpBackgroundColor

                Column {
                    id: lexiconElement

                    anchors {
                        fill: parent
                        margins: popUpListView.spacing / 2
                    }

                    spacing: popUpListView.spacing / 10


                    CustomText {
                        id: patternName

                        text: model.name
                        color: root.popUpTextColor
                        bold: true
                    }

                    Repeater {
                        model: uiBridge._lexiconNameModel._descriptionModel.getSizeForIndex(patternIndex)
                        Column {
                            id: multipleGridForOnePattern

                            width: parent.width

                            anchors {
                                rightMargin: 20
                            }
                            property int elementPatternIndex: index

                            spacing: 15
                            Rectangle {
                                width: parent.width
                                implicitHeight: descriptionText.implicitHeight
                                color: popUpElementBackgroundColor
                                CustomText {
                                    id: descriptionText
                                    text: uiBridge._lexiconNameModel._descriptionModel.getData(patternIndex, index, Qt.UserRole + 1)
                                    color: root.popUpTextColor
                                    textSize: 14
                                }

                            }
                            Rectangle {
                                id: gridRectangleOver

                                width: patternName.width
                                height: gridRectangle.height * 1.1

                                color: popUpElementBackgroundColor
                                border.color: root.popUpBorderElementColor
                                radius: 5


                                Rectangle {
                                    id: gridRectangle
                                    anchors.centerIn: parent
                                    width: patternGrid.width * 1.1
                                    height: patternGrid.height * 1.2

                                    color: root.cellDeadColor

                                    GridView {
                                        id: patternGrid
                                        anchors.centerIn: parent
                                        interactive: false

                                        width: cellWidth * uiBridge._lexiconNameModel._descriptionModel._gridModel.getColumnCountForIndex(patternIndex, elementPatternIndex)
                                        height: cellHeight * uiBridge._lexiconNameModel._descriptionModel._gridModel.getLineCountForIndex(patternIndex, elementPatternIndex)

                                        model: uiBridge._lexiconNameModel._descriptionModel._gridModel.getSizeForIndex(patternIndex, elementPatternIndex)

                                        cellWidth: 10
                                        cellHeight: 10

                                        delegate: Rectangle {

                                            width: patternGrid.cellWidth
                                            height: patternGrid.cellHeight


                                            layer {
                                                smooth: true
                                                enabled: true
                                            }
                                            color: uiBridge._lexiconNameModel._descriptionModel._gridModel.getData(patternIndex, elementPatternIndex, index, Qt.UserRole + 1) ? root.cellAliveColor : root.cellDeadColor


                                            border {
                                                width: 1
                                                color: root.gridBorderColor
                                            }
                                        }
                                        MouseArea {
                                            anchors.fill: parent
                                            onClicked: {
                                                if (uiBridge._lexiconNameModel._descriptionModel._gridModel.getSizeForIndex(patternIndex, elementPatternIndex) > 0) {

                                                    uiBridge.changePatternBackEnd(patternIndex, elementPatternIndex)
                                                    genericPopUp.close()
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    ActionButton {
        imgSource: "../assets/svg/clear.svg"
        anchors {
            top: parent.top
            right: parent.right
            rightMargin: parent.width / 20
            topMargin: parent.height / 40

        }
        onClicked: genericPopUp.close()
    }
}