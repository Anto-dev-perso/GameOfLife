import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

Slider {
    id: rootSlider

    width: parent.width * 0.6
    0
    to: 100

    background: Rectangle {
        id: sliderBackground

        x: rootSlider.leftPadding
        y: rootSlider.topPadding + rootSlider.availableHeight / 2 - height / 2
        height: rootSlider.width / 11
        width: rootSlider.availableWidth
        radius: sliderBackground.height / 2
        color: root.gameSlidersBackgroundUnSelectedColor

        Rectangle {
            id: slider

            width: rootSlider.visualPosition * parent.width
            height: parent.height
            color: root.gameSlidersBackgroundSelectedColor
            radius: parent.radius
        }
    }
    handle: Rectangle {
        id: sliderHandle

        x: rootSlider.leftPadding + rootSlider.visualPosition * (rootSlider.availableWidth - width)
        y: rootSlider.topPadding + rootSlider.availableHeight / 2 - height / 2
        implicitHeight: sliderBackground.height * 2
        implicitWidth: sliderHandle.height
        radius: width / 2
        color: root.gameSlidersHandleColor
    }
}
