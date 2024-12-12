import QtQuick

// TODO Upgrade in Qt6.8 and use VectorImage (https://doc.qt.io/qt-6/qtquick-vectorimage-example.html)
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
