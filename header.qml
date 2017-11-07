import QtQuick 2.0
import QtQuick.Controls 1.4

Rectangle {
    id: header
    color: "#363942"
    height: 48

    property int currntHeader: 1

    signal menuClicked

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
                        currntHeader = index + 1
                }

                source: 'qrc:/icon/header/' + centerHeader.headerName[index] + '-off.png'

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

        Repeater {
            model: ["undo", "history", "redo", "more"]

            ImageButton {
                height: header.height

                source: 'qrc:/icon/header/' + modelData + '.png'

                img: 'qrc:/icon/header/' + modelData + '.png'
                hover_img: 'qrc:/icon/header/' + modelData + '-hover.png'
                pressed_img: 'qrc:/icon/header/' + modelData + '-pressed.png'
            }
        }
    }
}
