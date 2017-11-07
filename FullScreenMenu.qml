import QtQuick 2.0

Rectangle {
    id: root
    signal returnClicked

    Row {
        anchors.fill: root

        Rectangle {
            id: sideBar
            color: "#eceeef"
            width: 368
            height: root.height

            Column {
                Repeater {
                    model: ['new', 'open', 'save']
                    ImageButton {
                        source: 'qrc:/icon/menu/' + modelData + '.png'

                        on_img: 'qrc:/icon/menu/' + modelData + '.png'
                        on_hover_img: 'qrc:/icon/menu/' + modelData + '-hover.png'
                        on_pressed_img: 'qrc:/icon/menu/' + modelData + '-pressed.png'
                        off_img: 'qrc:/icon/menu/' + modelData + '.png'
                        off_hover_img: 'qrc:/icon/menu/' + modelData + '-hover.png'
                        off_pressed_img: 'qrc:/icon/menu/' + modelData + '-pressed.png'

                        onClicked: root.returnClicked()
                    }
                }
            }


            Image {
                source: 'qrc:/icon/line.png'
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: sideBar.bottom
                anchors.bottomMargin: 20
            }
        }

        Rectangle {
            width: root.width - sideBar.width
            height: root.height
            color: "lightgrey"
            Rectangle {
                anchors.centerIn: parent
                Text {
                    anchors.centerIn: parent
                    font.family: 'Microsoft Yahei UI'
                    font.pixelSize: 50
                    text: '3D Paint'
                    color: "#0f568b"
                }
            }
        }
    }


}
