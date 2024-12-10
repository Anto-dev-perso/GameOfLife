import QtQuick

Image {
    id: customImg
    required property url imgSource
    property int dividerRatio: 1

    clip: true
    source: imgSource
    height: customImg.implicitHeight / dividerRatio

    asynchronous: true
    visible: imgSource !== ""

    fillMode: Image.PreserveAspectFit
    smooth: true
}
