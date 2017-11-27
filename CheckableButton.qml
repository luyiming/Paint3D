import QtQuick 2.0
import QtQuick.Controls 1.4

Image {
    id: root

    property url off_img: null
    property url off_hover_img: null
    property url off_pressed_img: null
    property url on_img: null
    property url on_hover_img: null
    property url on_pressed_img: null

    property bool checked: false

    property ExclusiveGroup exclusiveGroup: null

    onExclusiveGroupChanged: {
        if (exclusiveGroup)
            exclusiveGroup.bindCheckable(root)
    }

    signal clicked

    source: checked ? on_img : off_img

    onCheckedChanged: {
        if(mouseArea.containsMouse) {
            if (root.checked)
                root.source = on_hover_img
            else
                root.source = off_hover_img
        }
        else {
            if (root.checked)
                root.source = on_img
            else
                root.source = off_img
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true

        onClicked: {
            root.clicked()
            root.checked = true
        }

        onPressed: {
            if (root.checked)
                root.source = on_pressed_img
            else
                root.source = off_pressed_img
        }

        onReleased: {
            if(containsMouse) {
                if (root.checked)
                    root.source = on_hover_img
                else
                    root.source = off_hover_img
            }
            else {
                if (root.checked)
                    root.source = on_img
                else
                    root.source = off_img
            }
        }

        onContainsMouseChanged: {
            if(containsMouse) {
                if (root.checked)
                    root.source = on_hover_img
                else
                    root.source = off_hover_img
            }
            else {
                if (root.checked)
                    root.source = on_img
                else
                    root.source = off_img
            }
        }
    }
}
