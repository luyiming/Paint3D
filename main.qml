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
    height: 900
    title: qsTr("画图")

    Header {
        id: header
        anchors.top: root.top
        width: root.width
    }

    Panel1 {
        visible: header.currntHeader === 1
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

    Panel2 {
        visible: header.currntHeader === 2
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

        Rectangle {
            id: drawingboard
            anchors.centerIn: parent
            height: 480
            width: 640
            color: "#ffffff"
            DrawingBoard {
                anchors.fill: parent
                x1: 100
                y1: 100
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        parent.x1=mouseX;
                        parent.y1=mouseY;
                        parent.update()
                    }
                }
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
}
