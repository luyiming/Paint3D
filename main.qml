import QtQuick 2.6
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4
import luyiming 1.0

Window {
    id: root
    visible: true
    width: 1400
    minimumWidth: 1000
    height: 900
    minimumHeight: 700
    title: qsTr("画图")

    onWidthChanged: {
       if (root.width < 1000)
           root.width = 1000
    }

    Header {
        id: header
        anchors.top: root.top
        width: root.width

        onMenuClicked: {
            menuShowAnimation.start()
        }
    }

    BrushPanel {
        visible: header.currentHeader === 1
        id: panel
        width: 264
        height: root.height - header.height
        anchors.top: header.bottom
        anchors.bottom: root.bottom
        anchors.right: root.right
        anchors.left: board.right

        onVisibleChanged: {
            if (visible) {
                titleAnimation.start()
            }
        }
    }

    ShapePanel {
        visible: header.currentHeader === 2
        id: panel2
        width: 264
        height: root.height - header.height
        anchors.top: header.bottom
        anchors.bottom: root.bottom
        anchors.right: root.right
        anchors.left: board.right

        onVisibleChanged: {
            if (visible) {
                titleAnimation.start()
            }
        }
    }

    Rectangle {
        id: board
        color: "#b6b9b7"
        width: root.width - panel.width
        height: root.height - header.height
        anchors.top: header.bottom
        anchors.bottom: root.bottom
        anchors.left: root.left

        DrawingBoard {
            id: drawingboard
            anchors.centerIn: parent
            height: 480
            width: 640
            MouseArea {
                hoverEnabled: true
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                anchors.fill: parent
                onPressed: parent.handleMousePress(mouse.x, mouse.y, mouse.button, mouse.buttons, mouse.modifiers)
                onReleased: parent.handleMouseRelease(mouse.x, mouse.y, mouse.button, mouse.buttons, mouse.modifiers)
                onPositionChanged: parent.handleMouseMove(mouse.x, mouse.y, mouse.button, mouse.buttons, mouse.modifiers)
            }
        }

        DropShadow {
            anchors.fill: drawingboard
            horizontalOffset: 5
            verticalOffset: 5
            radius: 8.0
            samples: 17
            color: "#a0000000"
            source: drawingboard
        }

    }

    FullScreenMenu {
        id: menu
        color: "white"
        width: root.width
        height: root.height
        x: -root.width
        y: 0
        NumberAnimation {
            id: menuShowAnimation
            target: menu
            property: "x"
            duration: 200
            easing.type: Easing.InOutQuad
            from: -root.width
            to: 0
        }
        NumberAnimation {
            id: menuHideAnimation
            target: menu
            property: "x"
            duration: 200
            easing.type: Easing.InOutQuad
            from: 0
            to: -root.width
        }
        onReturnClicked: menuHideAnimation.start()
    }
}
