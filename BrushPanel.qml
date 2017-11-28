import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import luyiming 1.0

Rectangle {
    id: panel
    width: 264
    color: "#f0f2f3"

    property ParallelAnimation titleAnimation: titleAnimation
    property int instrument: DrawingBoard.INSTRUMENT_NONE

    ParallelAnimation {
        id: titleAnimation
        NumberAnimation {
            target: bigTitle
            property: "anchors.horizontalCenterOffset"
            duration: 250
            easing.type: Easing.InOutQuad
            from: 30
            to: 0
        }
        NumberAnimation {
            target: bigTitle
            property: "opacity"
            duration: 250
            easing.type: Easing.InOutQuad
            from: 0
            to: 1
        }
    }

    Text {
        id: bigTitle
        width: 220
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: panel.top
        anchors.topMargin: 12
        color: "#0064b6"
        font.pixelSize: 18
        font.family: "Microsoft Yahei UI"
        text: ''
    }

    ExclusiveGroup { id: shapeGroup }

    Grid {
        id: brushes
        width: 220
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: bigTitle.bottom
        anchors.topMargin: 12
        spacing: 5
        columns: 5

        property variant brushIconName: ["marker", "pen", "oil-brush", "watercolor", "pixel", "pencil", "eraser", "crayon", "spray-can", "fill"]
        property variant brushTitleName: ["马克笔", "钢笔", "油画笔", "水彩笔刷", "像素笔", "铅笔", "橡皮擦", "蜡笔", "喷雾罐", "填充"]
        property variant brushType: [DrawingBoard.INSTRUMENT_NONE, DrawingBoard.INSTRUMENT_NONE, DrawingBoard.INSTRUMENT_NONE, DrawingBoard.INSTRUMENT_NONE,
                                 DrawingBoard.BRUSH_PIXEL, DrawingBoard.INSTRUMENT_NONE, DrawingBoard.INSTRUMENT_NONE, DrawingBoard.INSTRUMENT_NONE,
                                 DrawingBoard.INSTRUMENT_NONE, DrawingBoard.INSTRUMENT_NONE]
        Repeater {
            model: 10

            CheckableButton {
                width: 40
                height: 40

                exclusiveGroup: shapeGroup

                source: 'qrc:/icon/brush/' + brushes.brushIconName[index] + '.png'

                on_img: 'qrc:/icon/brush/' + brushes.brushIconName[index] + '-on.png'
                on_hover_img: 'qrc:/icon/brush/' + brushes.brushIconName[index] + '-on.png'
                on_pressed_img: 'qrc:/icon/brush/' + brushes.brushIconName[index] + '-on.png'
                off_img: 'qrc:/icon/brush/' + brushes.brushIconName[index] + '.png'
                off_hover_img: 'qrc:/icon/brush/' + brushes.brushIconName[index] + '-hover.png'
                off_pressed_img: 'qrc:/icon/brush/' + brushes.brushIconName[index] + '-hover.png'

                onCheckedChanged: {
                    if (checked && bigTitle.text !== brushes.brushTitleName[index]) {
                        bigTitle.text = brushes.brushTitleName[index]
                        titleAnimation.start()
                        panel.instrument = brushes.brushType[index]
                    }
                }
            }
        }

    }


    Item {
        id: title3
        width: 220
        height: 30
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: brushes.bottom
        anchors.topMargin: 12
        Text {
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            color: "#4d4d75"
            font.pixelSize: 13
            font.family: "Microsoft Yahei UI"
            text: '粗细'
        }
        Rectangle {
            anchors.right: parent.right
            height: 30
            width: 85
            color: "#ffffff"
            border.color: "grey"
            border.width: 1

            TextEdit {
                readOnly: true
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
                text: thickness.value + '像素'
                font.pixelSize: 13
                font.family: "Microsoft Yahei UI"
                color: '#757675'
            }
        }
    }



    Slider {
        id: thickness
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: title3.bottom
        anchors.topMargin: 12
        width: 216
        height: 44
        minimumValue: 1
        maximumValue: 100
        stepSize: 1
        value: 2

        style: SliderStyle {
            groove: Rectangle {
                implicitWidth: parent.width
                implicitHeight: 2
                color: "lightgrey"
            }
            handle: Rectangle {
                anchors.centerIn: parent
                color: control.pressed ? "grey" : "#0064b6"
                implicitWidth: 8
                implicitHeight: 25
                radius: 5
            }
        }
    }

    Item {
        id: title4
        width: 220
        height: 30
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: thickness.bottom
        anchors.topMargin: 12
        Text {
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            color: "#4d4d75"
            font.pixelSize: 13
            font.family: "Microsoft Yahei UI"
            text: '不透明度'
        }
        Rectangle {
            anchors.right: parent.right
            height: 30
            width: 85
            color: "#ffffff"
            border.color: "grey"
            border.width: 1

            TextEdit {
                readOnly: true
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
                text: opaqueness.value + '%'
                font.pixelSize: 13
                font.family: "Microsoft Yahei UI"
                color: '#757675'
            }
        }
    }

    Slider {
        id: opaqueness
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: title4.bottom
        anchors.topMargin: 12
        width: 216
        height: 44
        minimumValue: 1
        maximumValue: 100
        stepSize: 1
        value: 100

        style: SliderStyle {
            groove: Rectangle {
                implicitWidth: parent.width
                implicitHeight: 2
                color: "lightgrey"
            }
            handle: Rectangle {
                anchors.centerIn: parent
                color: control.pressed ? "grey" : "#0064b6"
                implicitWidth: 8
                implicitHeight: 25
                radius: 5
            }
        }
    }

    Image {
        source: 'qrc:/icon/line.png'
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: currentColor.top
        anchors.bottomMargin: 20
    }

    Rectangle {
        id: currentColor
        width: 140
        height: 44
        anchors.bottom: colorPanel.top
        anchors.bottomMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        color: "#ffffff"
        border.width: 0
        border.color: "#305ccc"
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            onContainsMouseChanged: {
                if(containsMouse) {
                    parent.border.width = 1
                }
                else {
                    parent.border.width = 0
                }
            }
            onClicked: {

            }
        }
    }

    Grid {
        id: colorPanel
        width: 220
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 20
        columns: 6

        property variant colorArray: ["#ffffff", "#c3c3c3", "#585858", "#000000", "#88001b", "#ec1c24",
            "#ff7f27", "#ffca18", "#fdeca6", "#fff200", "#c4ff0e", "#0ed145",
            "#8cfffb", "#00a8f3", "#3f48cc", "#b83dba", "#ffaec8", "#b97a56"]

        Repeater {
            model: 18
            Rectangle {
                width: 36; height: 36
                color: colorPanel.colorArray[index]
                border.color: Qt.darker(color)
                border.width: 0
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onContainsMouseChanged: {
                        if(containsMouse) {
                            parent.border.width = 2
                        }
                        else {
                            parent.border.width = 0
                        }
                    }
                }
            }
        }
    }
}
