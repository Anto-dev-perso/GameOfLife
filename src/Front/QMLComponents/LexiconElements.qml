import QtQuick
import QtQuick.Controls

ScrollView {
    id: lexiconScroll

    //required property int mySpacing
    ListView {
        id: popUpListView

        //property alias spacing: popUpListView.spacing
        //spacing: lexiconScroll.mySpacing
        spacing: lexiconScroll.height / 20

        model: uiBridge._lexiconNameModel
        cacheBuffer: currentItem.implicitHeight * 40
        clip: true

        delegate: Loader {
            sourceComponent: Rectangle {
                id: rootPatternElement

                width: popUpListView.width - popUpListView.spacing
                implicitHeight: 50 + lexiconElement.implicitHeight

                radius: popUpListView.spacing / 10
                property int patternIndex: index

                anchors.horizontalCenter: parent.horizontalCenter

                color: root.popUpElementBackgroundColor
                border.color: root.popUpBackgroundColor

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
                        model: uiBridge._lexiconNameModel._descriptionModel.getSizeForIndex(
                                   patternIndex)
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
                                color: root.popUpElementBackgroundColor
                                CustomText {
                                    id: descriptionText
                                    text: uiBridge._lexiconNameModel._descriptionModel.getData(
                                              patternIndex, index,
                                              Qt.UserRole + 1)
                                    color: root.popUpTextColor
                                    textSize: 14
                                }
                            }
                            Rectangle {
                                id: gridRectangleOver

                                width: patternName.width
                                height: gridRectangle.height * 1.5

                                color: root.popUpElementBackgroundColor
                                border.color: root.popUpBorderElementColor
                                radius: 5

                                Rectangle {
                                    id: gridRectangle
                                    anchors.centerIn: parent
                                    width: imgLoader.implicitWidth * 1.05
                                    height: imgLoader.implicitHeight * 1.1

                                    color: root.cellDeadColor
                                    Loader {
                                        id: imgLoader

                                        width: patternGrid.implicitWidth
                                        height: patternGrid.implicitHeight
                                        anchors.fill: parent
                                        sourceComponent: uiBridge.fileExists(
                                                             patternIndex,
                                                             elementPatternIndex) ? patternGrid : null
                                    }
                                    Component {
                                        id: patternGrid
                                        Image {
                                            source: "../assets/svg/lexicon/pattern_" + patternIndex
                                                    + "_" + elementPatternIndex + ".svg"
                                            fillMode: Image.PreserveAspectFit
                                            anchors.centerIn: parent
                                            MouseArea {
                                                anchors.fill: parent
                                                onClicked: {
                                                    // TODO 2*183 ms from the profiler
                                                    if (uiBridge._lexiconNameModel._descriptionModel._gridModel.getSizeForIndex(
                                                                patternIndex,
                                                                elementPatternIndex) > 0) {

                                                        uiBridge.changePatternBackEnd(
                                                                    patternIndex,
                                                                    elementPatternIndex)
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
    }
}
