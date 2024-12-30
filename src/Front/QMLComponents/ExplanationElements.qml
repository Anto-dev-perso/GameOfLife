import QtQuick
import QtQuick.Controls

ScrollView {
    id: explanantionRoot
    contentItem: Flickable {
        id: flickable

        property int elementsSpacing: parent.width / 15

        contentWidth: parent.width
        contentHeight: column.height + flickable.elementsSpacing

        clip: true
        Column {
            id: column

            width: parent.width - flickable.elementsSpacing
            anchors.centerIn: parent

            spacing: flickable.elementsSpacing

            CustomText {
                id: title
                text: "Game of Life Explanation"
                bold: true
                color: root.popUpTextColor
                textSize: 24
            }
            CustomText {
                id: intro1
                text: "The Game of Life is not your typical computer game. It is a cellular automaton, and was invented by Cambridge mathematician John Conway."
                color: root.popUpTextColor
            }
            CustomText {
                id: intro2
                text: "This game became widely known when it was mentioned in an article published by Scientific American in 1970. It consists of a grid of cells which, based on a few mathematical rules, cal live, die or multiply. Depending on the initial conditions, the cells form various patterns throughtout the course of the game"
                color: root.popUpTextColor
            }

            Rectangle {
                width: parent.width
                implicitHeight: rulesGrid.implicitHeight
                color: root.popUpBackgroundColor
                border.color: root.popUpBorderElementColor
                radius: 10
                Grid {
                    id: rulesGrid
                    width: parent.width
                    padding: 20
                    columns: 2

                    spacing: effectiveWidth * 0.02

                    readonly property int effectiveWidth: (rulesGrid.width - 2 * rulesGrid.padding)
                    columnSpacing: effectiveWidth * 0.03

                    property int leftElementWidth: effectiveWidth * 0.65
                    property int rightElementWidth: effectiveWidth - leftElementWidth
                        - spacing - columnSpacing
                    property int elementHeight: 50
                    CustomText {
                        text: "Rules"
                        bold: true
                        color: root.popUpTextColor
                        textSize: 20
                        width: rulesGrid.leftElementWidth
                        height: rulesGrid.elementHeight
                    }
                    CustomText {
                        width: rulesGrid.rightElementWidth
                        height: rulesGrid.elementHeight
                        text: ""
                        color: root.popUpTextColor
                    }
                    CustomText {
                        width: rulesGrid.leftElementWidth
                        text: "For a space that is populated:"
                        bold: true
                        color: root.popUpTextColor
                    }
                    CustomText {
                        width: rulesGrid.rightElementWidth
                        height: rulesGrid.elementHeight
                        text: "Examples"
                        bold: true
                        color: root.popUpTextColor
                    }

                    CustomText {
                        text: "Each cell with one or no neighbors dies, as if by solitude."
                        color: root.popUpTextColor
                        italic: true
                        width: rulesGrid.leftElementWidth
                        height: rulesGrid.elementHeight
                    }
                    ExplanationExamples {
                        width: rulesGrid.rightElementWidth
                        height: rulesGrid.elementHeight
                        imgLeftSource: "../assets/png/example_1.1.png"
                        imgRightSource: "../assets/png/example_1.2.png"
                    }

                    CustomText {
                        text: "Each cell with four or more neighbors dies, as if by overpopulation."
                        color: root.popUpTextColor
                        italic: true
                        width: rulesGrid.leftElementWidth
                        height: rulesGrid.elementHeight
                    }
                    ExplanationExamples {
                        width: rulesGrid.rightElementWidth
                        height: rulesGrid.elementHeight
                        imgLeftSource: "../assets/png/example_5.1.png"
                        imgRightSource: "../assets/png/example_5.2.png"
                    }

                    CustomText {
                        text: "Each cell with two or three neighbors survives."
                        color: root.popUpTextColor
                        italic: true
                        width: rulesGrid.leftElementWidth
                        height: rulesGrid.elementHeight
                    }
                    ExplanationExamples {
                        width: rulesGrid.rightElementWidth
                        height: rulesGrid.elementHeight
                        imgLeftSource: "../assets/png/example_2.1.png"
                        imgRightSource: "../assets/png/example_2.2.png"
                    }

                    CustomText {
                        text: "For a space that is empty or unpopulated"
                        bold: true
                        color: root.popUpTextColor
                        width: rulesGrid.leftElementWidth
                        height: rulesGrid.elementHeight
                    }
                    CustomText {
                        width: rulesGrid.rightElementWidth
                        height: rulesGrid.elementHeight
                        text: ""
                        color: root.popUpTextColor
                    }

                    CustomText {
                        text: "Each cell with three neighbors becomes populated."
                        color: root.popUpTextColor
                        italic: true
                        width: rulesGrid.leftElementWidth
                        height: rulesGrid.elementHeight
                    }
                    ExplanationExamples {
                        width: rulesGrid.rightElementWidth
                        height: rulesGrid.elementHeight
                        imgLeftSource: "../assets/png/example_3.1.png"
                        imgRightSource: "../assets/png/example_3.2.png"
                    }
                }
            }

            CustomText {
                id: moreIfo
                text: "More Information"
                bold: true
                color: root.popUpTextColor
            }
            CustomText {
                id: videosIntro
                text: "Video's about the Game of Life"
                color: root.popUpTextColor
            }
            Grid {
                //Row
                id: youtubeGrid
                width: parent.width
                //            height: 100
                columns: 2


                property string videoUrl: "https://www.youtube.com/watch?v="

                property int imgWidth: youtubeGrid.width / 4
                property int imgHeight: youtubeGrid.imgWidth * 9 / 16 // Respect 16:9 ratio

                Item {
                    width: parent.width / 2
                    height: youtubeGrid.imgHeight
                    Image {
                        id: hawking

                        property string videoId: "CgOcEZinQ2I"
                        source: "../assets/png/yt-hawkins.jpg"
                        width: youtubeGrid.imgWidth
                        height: youtubeGrid.imgHeight
                        anchors.centerIn: parent
                        fillMode: Image.PreserveAspectCrop
                        smooth: true
                        clip: true
                        MouseArea {
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                            onClicked: Qt.openUrlExternally(
                                youtubeGrid.videoUrl + hawking.videoId)
                        }
                    }
                }

                Item {
                    width: parent.width / 2
                    height: youtubeGrid.imgHeight
                    CustomImage {
                        id: conway

                        property string videoId: "R9Plq-D1gEk"

                        imgSource: "../assets/png/yt-numberphile.jpg"

                        width: youtubeGrid.imgWidth
                        height: youtubeGrid.imgHeight
                        anchors.centerIn: parent
                        fillMode: Image.PreserveAspectCrop
                        smooth: true
                        clip: true
                        MouseArea {
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                            onClicked: Qt.openUrlExternally(
                                youtubeGrid.videoUrl + conway.videoId)
                        }
                    }
                }
                Item {
                    width: parent.width / 2
                    height: hawkingText.implicitHeight
                    CustomText {
                        id: hawkingText
                        width: youtubeGrid.imgWidth
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: parent.top

                        text: "The rules are explained in Stehpen Hawkings' documentary The Meaning of Life"
                        color: root.popUpTextColor
                        textSize: 12
                    }
                }
                Item {
                    width: parent.width / 2
                    height: conwayText.implicitHeight
                    CustomText {
                        id: conwayText
                        width: youtubeGrid.imgWidth
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: parent.top

                        text: "John Conway himself talks about the Game of Life"
                        color: root.popUpTextColor
                        textSize: 12
                    }
                }
            }
            CustomText {
                id: thankText
                topPadding: rulesGrid.elementHeight / 2
                color: root.popUpTextColor
                textFormat: Text.RichText
                text: "This program is reproduction of the Edwin Martin's website <a href='https://playgameoflife.com/'>playgameoflife.com/</a>."
                onLinkActivated: link => Qt.openUrlExternally(link)
                HoverHandler {
                    enabled: parent.hoveredLink
                    cursorShape: Qt.PointingHandCursor
                }
            }
        }
    }
}
