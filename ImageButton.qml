import QtQuick 2.0
import QtQuick.Controls 1.4

Image {
    id: root
    property url img: null
    property url hover_img: null
    property url pressed_img: null

    signal clicked

    source: img

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true

        onClicked: {
            root.clicked()
        }

        onPressed: {
            root.source = pressed_img
        }

        onReleased: {
            if (containsMouse)
                root.source = hover_img
            else
                root.source = img
        }

        onEntered: root.source = hover_img

        onExited: root.source = img

    }
}
