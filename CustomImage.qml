import QtQuick

Image {

    required property url imgSource

    source: imgSource
    width: 30
    height: 30

    fillMode: Image.PreserveAspectFit
    smooth: true
}
