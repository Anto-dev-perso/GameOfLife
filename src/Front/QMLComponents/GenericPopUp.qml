import QtQuick
import QtQuick.Controls

Popup {
    id: genericPopUp
    enum PopUpType {
        LEXICON,
        EXPLANATION
    }

    required property int contentOfPopUp

    modal: true
    focus: true

    width: root.popUpWidth
    height: root.popUpHeight

    anchors.centerIn: parent

    contentItem: Loader {
        sourceComponent: genericPopUp.contentOfPopUp
                         === GenericPopUp.PopUpType.LEXICON ? lexicon : explanation
    }

    Component {
        id: lexicon
        LexiconElements {}
    }

    Component {
        id: explanation
        ExplanationElements {}
    }

    ActionButton {
        z: 1
        imgSource: "../assets/svg/buttons/clear.svg"
        anchors {
            top: parent.top
            right: parent.right
            rightMargin: parent.width / 20
            topMargin: parent.height / 40
        }
        paddingLeft: -7
        paddingTop: -9
        onClicked: genericPopUp.close()
    }
}
