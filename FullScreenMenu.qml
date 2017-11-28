import QtQuick 2.0
import QtQuick.Dialogs 1.2

Rectangle {
    id: root
    signal returnClicked

    FileDialog {
        id: saveFileDialog
        title: "Please choose a file"
        folder: "."
        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrls)
        }
        onRejected: {
            console.log("Canceled")
        }
    }

    Row {
        anchors.fill: root

        Rectangle {
            id: sideBar
            color: "#eceeef"
            width: 368
            height: root.height

            Column {
                ImageButton {
                    img: 'qrc:/icon/menu/return.png'
                    hover_img: 'qrc:/icon/menu/return-hover.png'
                    pressed_img: 'qrc:/icon/menu/return-pressed.png'
                    onClicked: root.returnClicked()
                }

                Repeater {
                    model: ['new', 'open', 'save']
                    CheckableButton {
                        source: 'qrc:/icon/menu/' + modelData + '.png'

                        on_img: 'qrc:/icon/menu/' + modelData + '.png'
                        on_hover_img: 'qrc:/icon/menu/' + modelData + '-hover.png'
                        on_pressed_img: 'qrc:/icon/menu/' + modelData + '-pressed.png'
                        off_img: 'qrc:/icon/menu/' + modelData + '.png'
                        off_hover_img: 'qrc:/icon/menu/' + modelData + '-hover.png'
                        off_pressed_img: 'qrc:/icon/menu/' + modelData + '-pressed.png'

                        onClicked: saveFileDialog.open()
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
                Column {
                    anchors.centerIn: parent
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.family: 'Microsoft Yahei UI'
                        font.pixelSize: 50
                        text: '3D Paint'
                        color: "#0064b6"
                    }
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.family: 'Microsoft Yahei UI'
                        font.pixelSize: 30
                        text: 'Lu Yiming'
                        color: "grey"
                    }
                }
            }
        }
    }


}
