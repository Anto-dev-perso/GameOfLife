import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

Slider {
    id: rootSlider

    // width: parent.width * 0.6
    width: 100
    height: width / 10
    from: 0
    to: 100

    background: Rectangle {
        id: sliderBackground
        radius: rootSlider.height / 2
        color: root.gameSlidersBackgroundUnSelectedColor
        Rectangle {
            id: slider

            width: rootSlider.visualPosition * parent.width
            height: parent.height
            color: root.gameSlidersBackgroundSelectedColor
            topLeftRadius: height / 2
            bottomLeftRadius: height / 2
        }
    }
    handle: Rectangle {
        id: sliderHandle

        width: rootSlider.height * 1.8
        height: rootSlider.height * 1.8
        x: ((rootSlider.value - rootSlider.from) / (rootSlider.to - rootSlider.from)) * (rootSlider.width - width)
        y: (rootSlider.height - height) / 2

        radius: rootSlider.width / 2
        color: root.gameSlidersHandleColor
    }
}
