import QtQuick 2.0
import QtQuick.Controls 1.4

Rectangle {
    id: header
    color: "#54575d"
    height: 48

    property int currntHeader: 1

    ImageButton {
        id: menu_button
        width: 68
        height: header.height
        anchors.left: parent.left
        source: 'qrc:/icon/header-menu-off.png'

        on_img: 'qrc:/icon/header-menu-off.png'
        on_hover_img: 'qrc:/icon/header-menu-off-hover.png'
        on_pressed_img: 'qrc:/icon/header-menu-off-pressed.png'
        off_img: 'qrc:/icon/header-menu-off.png'
        off_hover_img: 'qrc:/icon/header-menu-off-hover.png'
        off_pressed_img: 'qrc:/icon/header-menu-off-pressed.png'
    }

    Row {
        ExclusiveGroup { id: headerGroup }

        anchors.centerIn: header

        ImageButton {
            id: brush_button
            width: 68
            height: header.height
            exclusiveGroup: headerGroup
            checked: true

            onCheckedChanged: {
                if (checked)
                    currntHeader = 1
            }

            source: 'qrc:/icon/header-brush-off.png'

            on_img: 'qrc:/icon/header-brush-on.png'
            on_hover_img: 'qrc:/icon/header-brush-on-hover.png'
            on_pressed_img: 'qrc:/icon/header-brush-on.png'
            off_img: 'qrc:/icon/header-brush-off.png'
            off_hover_img: 'qrc:/icon/header-brush-off-hover.png'
            off_pressed_img: 'qrc:/icon/header-brush-off.png'
        }

        ImageButton {
            id: shape2d_button
            width: 68
            height: header.height
            exclusiveGroup: headerGroup

            onCheckedChanged: {
                if (checked)
                    currntHeader = 2
            }

            source: 'qrc:/icon/header-2dshape-off.png'

            on_img: 'qrc:/icon/header-2dshape-on.png'
            on_hover_img: 'qrc:/icon/header-2dshape-on-hover.png'
            on_pressed_img: 'qrc:/icon/header-2dshape-on.png'
            off_img: 'qrc:/icon/header-2dshape-off.png'
            off_hover_img: 'qrc:/icon/header-2dshape-off-hover.png'
            off_pressed_img: 'qrc:/icon/header-2dshape-off.png'
        }

        ImageButton {
            id: shape3d_button
            width: 68
            height: header.height
            exclusiveGroup: headerGroup

            source: 'qrc:/icon/header-3dshape-off.png'

            on_img: 'qrc:/icon/header-3dshape-on.png'
            on_hover_img: 'qrc:/icon/header-3dshape-on-hover.png'
            on_pressed_img: 'qrc:/icon/header-3dshape-on.png'
            off_img: 'qrc:/icon/header-3dshape-off.png'
            off_hover_img: 'qrc:/icon/header-3dshape-off-hover.png'
            off_pressed_img: 'qrc:/icon/header-3dshape-off.png'
        }
    }

}
