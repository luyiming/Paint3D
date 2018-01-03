import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

Rectangle {
    id: root
    signal returnClicked
    signal newButtonClicked

    FileDialog {
        id: openFileDialog
        title: qsTr("请选择一个图片文件")
        folder: "."
        nameFilters: [ "Image files (*.jpg *.png)" ]
        onAccepted: {
            drawingboard.openFile(openFileDialog.fileUrl)
            root.returnClicked()
//            console.log("Open file: " + openFileDialog.fileUrls)
        }
    }
    FileDialog {
        id: saveFileDialog
        title: qsTr("请选择一个文件夹")
        folder: "."
        selectFolder: true
        onAccepted: {
            drawingboard.saveFile(saveFileDialog.folder)
//            console.log("Save file: " + saveFileDialog.fileUrls)
        }
    }

    RowLayout {
        spacing: 0
        anchors.fill: root

        Rectangle {
            id: sideBar
            color: "#eceeef"
            width: 368
            height: root.height

            ColumnLayout {
                ImageButton {
                    id: returnButton
                    img: 'qrc:/icon/menu/return.png'
                    hover_img: 'qrc:/icon/menu/return-hover.png'
                    pressed_img: 'qrc:/icon/menu/return-pressed.png'
                    onClicked: root.returnClicked()
                }
                CheckableButton {
                    id: newButton
                    source: 'qrc:/icon/menu/new.png'

                    on_img: 'qrc:/icon/menu/new.png'
                    on_hover_img: 'qrc:/icon/menu/new-hover.png'
                    on_pressed_img: 'qrc:/icon/menu/new-pressed.png'
                    off_img: 'qrc:/icon/menu/new.png'
                    off_hover_img: 'qrc:/icon/menu/new-hover.png'
                    off_pressed_img: 'qrc:/icon/menu/new-pressed.png'

                    onClicked: newButtonClicked()
                }
                CheckableButton {
                    id: openButton
                    source: 'qrc:/icon/menu/open.png'

                    on_img: 'qrc:/icon/menu/open.png'
                    on_hover_img: 'qrc:/icon/menu/open-hover.png'
                    on_pressed_img: 'qrc:/icon/menu/open-pressed.png'
                    off_img: 'qrc:/icon/menu/open.png'
                    off_hover_img: 'qrc:/icon/menu/open-hover.png'
                    off_pressed_img: 'qrc:/icon/menu/open-pressed.png'

                    onClicked: openFileDialog.open()
                }
                CheckableButton {
                    id: saveButton
                    source: 'qrc:/icon/menu/save.png'

                    on_img: 'qrc:/icon/menu/save.png'
                    on_hover_img: 'qrc:/icon/menu/save-hover.png'
                    on_pressed_img: 'qrc:/icon/menu/save-pressed.png'
                    off_img: 'qrc:/icon/menu/save.png'
                    off_hover_img: 'qrc:/icon/menu/save-hover.png'
                    off_pressed_img: 'qrc:/icon/menu/save-pressed.png'

                    onClicked: saveFileDialog.open()
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
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
