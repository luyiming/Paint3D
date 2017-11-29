import QtQuick 2.0
import QtQuick.Controls 1.4

Rectangle {
    id: header
    color: "#363942"
    height: 48

    property int currentHeader: 1
    property bool canUndo: false
    property bool canRedo: false

    signal menuClicked
    signal undoClicked
    signal redoClicked

    ImageButton {
        id: menu_button
        width: 68
        height: header.height
        anchors.left: parent.left
        source: 'qrc:/icon/header/menu.png'

        img: 'qrc:/icon/header/menu.png'
        hover_img: 'qrc:/icon/header/menu-hover.png'
        pressed_img: 'qrc:/icon/header/menu-pressed.png'

        onClicked: header.menuClicked()
    }

    Row {
        id: centerHeader
        ExclusiveGroup { id: headerGroup }

        anchors.centerIn: header
        anchors.horizontalCenterOffset: -128

        property variant headerName: ["brush", "2dshape", "3dshape", "text", "effects", "canvas"]

        Repeater {
            model: 6

            CheckableButton {
                width: 68
                height: header.height
                exclusiveGroup: headerGroup

                onCheckedChanged: {
                    if (checked)
                        currentHeader = index + 1
                }

                on_img: 'qrc:/icon/header/' + centerHeader.headerName[index] + '-on.png'
                on_hover_img: 'qrc:/icon/header/' + centerHeader.headerName[index] + '-on-hover.png'
                on_pressed_img: 'qrc:/icon/header/' + centerHeader.headerName[index] + '-on.png'
                off_img: 'qrc:/icon/header/' + centerHeader.headerName[index] + '-off.png'
                off_hover_img: 'qrc:/icon/header/' + centerHeader.headerName[index] + '-off-hover.png'
                off_pressed_img: 'qrc:/icon/header/' + centerHeader.headerName[index] + '-off.png'
            }
        }

    }

    Row {
        id: rightHeader

        anchors.right: header.right

        ImageButton {
            height: header.height

            source: 'qrc:/icon/header/undo.png'

            img: 'qrc:/icon/header/undo.png'
            hover_img: 'qrc:/icon/header/undo-hover.png'
            pressed_img: 'qrc:/icon/header/undo-pressed.png'

            onClicked: header.undoClicked()
            enabled: canUndo
        }
        ImageButton {
            height: header.height

            source: 'qrc:/icon/header/history.png'

            img: 'qrc:/icon/header/history.png'
            hover_img: 'qrc:/icon/header/history-hover.png'
            pressed_img: 'qrc:/icon/header/history-pressed.png'

            enabled: false
        }
        ImageButton {
            height: header.height

            source: 'qrc:/icon/header/redo.png'

            img: 'qrc:/icon/header/redo.png'
            hover_img: 'qrc:/icon/header/redo-hover.png'
            pressed_img: 'qrc:/icon/header/redo-pressed.png'

            onClicked: header.redoClicked()
            enabled: canRedo
        }
        ImageButton {
            height: header.height

            source: 'qrc:/icon/header/more.png'

            img: 'qrc:/icon/header/more.png'
            hover_img: 'qrc:/icon/header/more-hover.png'
            pressed_img: 'qrc:/icon/header/more-pressed.png'
        }
    }
}
