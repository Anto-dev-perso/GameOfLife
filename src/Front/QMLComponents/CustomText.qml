import QtQuick

Text {
    id: customText
    property alias text: customText.text
    property alias bold: customText.font.bold
    property alias italic: customText.font.italic
    property int textSize: 18
    property alias color: customText.color

    width: parent.width
    wrapMode: Text.Wrap


    font.pixelSize: textSize
}
