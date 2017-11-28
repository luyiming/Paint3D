import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
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
            property: "Layout.leftMargin"
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

    ColumnLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: panel.top
        anchors.topMargin: 12
        spacing: 12

        Text {
            id: bigTitle
            width: 220
            color: "#0064b6"
            font.pixelSize: 18
            font.family: "Microsoft Yahei UI"
            text: '2D图形'
        }

        ExclusiveGroup { id: shapeGroup }

        Text {
            width: 220
            Layout.topMargin: 3
            color: "#4d4d75"
            font.pixelSize: 13
            font.family: "Microsoft Yahei UI"
            text: '直线和曲线'
        }

        Row {
            id: lines_and_curves
            width: 220

            property variant shapeIconName: ["line", "curve2", "curve3", "curve4"]
            property variant shapeTitleName: ["直线", "两点曲线", "三点曲线", "四点曲线"]
            property variant shapeType: [DrawingBoard.SHAPE_LINE, DrawingBoard.INSTRUMENT_NONE, DrawingBoard.INSTRUMENT_NONE, DrawingBoard.INSTRUMENT_NONE]

            Repeater {
                model: 4

                CheckableButton {
                    width: 40
                    height: 40

                    exclusiveGroup: shapeGroup

                    source: 'qrc:/icon/2dshape/' + lines_and_curves.shapeIconName[index] + '.png'

                    on_img: 'qrc:/icon/2dshape/' + lines_and_curves.shapeIconName[index] + '-on.png'
                    on_hover_img: 'qrc:/icon/2dshape/' + lines_and_curves.shapeIconName[index] + '-on.png'
                    on_pressed_img: 'qrc:/icon/2dshape/' + lines_and_curves.shapeIconName[index] + '-on.png'
                    off_img: 'qrc:/icon/2dshape/' + lines_and_curves.shapeIconName[index] + '.png'
                    off_hover_img: 'qrc:/icon/2dshape/' + lines_and_curves.shapeIconName[index] + '-on.png'
                    off_pressed_img: 'qrc:/icon/2dshape/' + lines_and_curves.shapeIconName[index] + '-pressed.png'

                    onCheckedChanged: {
                        if (checked && bigTitle.text !== lines_and_curves.shapeTitleName[index]) {
                            bigTitle.text = lines_and_curves.shapeTitleName[index]
                            titleAnimation.start()
                            panel.instrument = lines_and_curves.shapeType[index]
                        }
                    }
                }
            }
        }

        Text {
            width: 220
            color: "#4d4d75"
            font.pixelSize: 13
            font.family: "Microsoft Yahei UI"
            text: '2D 形状'
        }

        Grid {
            id: shapes
            width: 220
            columns: 5
            spacing: 5

            property variant shapeIconName: ["circle", "capsule", "square", "rounded-square", "triangle",
                "pentagon", "hexagon", "diamond", "right-triangle", "arrow",
                "pointed-arrow", "arc", "five-pointed-star", "six-pointed-star", "four-pointed-star"]
            property variant shapeTitleName: ["圆形", "胶囊形", "矩形", "圆角矩形", "三角形",
                "五边形", "六边形", "菱形", "直角三角形", "arrow",
                "pointed-arrow", "圆弧", "五角星", "六角星", "四角星"]
            property variant shapeType: [DrawingBoard.INSTRUMENT_NONE, DrawingBoard.INSTRUMENT_NONE, DrawingBoard.INSTRUMENT_NONE, DrawingBoard.INSTRUMENT_NONE, DrawingBoard.INSTRUMENT_NONE,
                DrawingBoard.INSTRUMENT_NONE, DrawingBoard.INSTRUMENT_NONE, DrawingBoard.INSTRUMENT_NONE, DrawingBoard.INSTRUMENT_NONE, DrawingBoard.INSTRUMENT_NONE,
                DrawingBoard.INSTRUMENT_NONE, DrawingBoard.INSTRUMENT_NONE, DrawingBoard.INSTRUMENT_NONE, DrawingBoard.INSTRUMENT_NONE, DrawingBoard.INSTRUMENT_NONE]

            Repeater {
                model: 15

                CheckableButton {
                    width: 40
                    height: 40

                    exclusiveGroup: shapeGroup

                    source: 'qrc:/icon/2dshape/' + shapes.shapeIconName[index] + '.png'

                    on_img: 'qrc:/icon/2dshape/' + shapes.shapeIconName[index] + '-on.png'
                    on_hover_img: 'qrc:/icon/2dshape/' + shapes.shapeIconName[index] + '-on.png'
                    on_pressed_img: 'qrc:/icon/2dshape/' + shapes.shapeIconName[index] + '-on.png'
                    off_img: 'qrc:/icon/2dshape/' + shapes.shapeIconName[index] + '.png'
                    off_hover_img: 'qrc:/icon/2dshape/' + shapes.shapeIconName[index] + '-on.png'
                    off_pressed_img: 'qrc:/icon/2dshape/' + shapes.shapeIconName[index] + '-pressed.png'

                    onCheckedChanged: {
                        if (checked && bigTitle.text !== shapes.shapeTitleName[index]) {
                            bigTitle.text = shapes.shapeTitleName[index]
                            titleAnimation.start()
                            panel.instrument = shapes.shapeType[index]
                            panel.instrumentChanged()
                        }
                    }
                }
            }
        }

        SliderWithBox {
            id: thicknessSlider
            Layout.topMargin: 10
            width: 220
            title: '粗细'
            postfixText: '像素'
            minimumValue: 1
            maximumValue: 100
            stepSize: 1
            value: 1
        }

        SliderWithBox {
            id: opaquenessSlider
            width: 220
            title: '不透明度'
            postfixText: '%'
            minimumValue: 1
            maximumValue: 100
            stepSize: 1
            value: 100
        }
    }


    ColorDialog {
        id: boarderColorDialog
        showAlphaChannel: true
        onAccepted: {
            boarderColorBlock.color = boarderColorDialog.color
        }
    }

    ColorDialog {
        id: fillColorDialog
        showAlphaChannel: true
        onAccepted: {
            fillColorBlock.color = fillColorDialog.color
        }
    }

    ColumnLayout {
        anchors.bottom: panel.bottom
        anchors.bottomMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 12
        Image {
            source: 'qrc:/icon/line.png'
        }

        Text {
            width: 220
            Layout.topMargin: 3
            color: "#4d4d75"
            font.pixelSize: 13
            font.family: "Microsoft Yahei UI"
            text: '边框颜色'
        }

        RowLayout {
            Rectangle {
                width: 50
                height: 50
                color: "#f0f2f3"
                border.width: 1
                border.color: "#d2d2d2"
                Rectangle {
                    id: boarderColorBlock
                    width: 30
                    height: 30
                    color: "#000000"
                    anchors.centerIn: parent
                }
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onContainsMouseChanged: {
                        if(containsMouse) {
                            parent.border.color = "#305ccc"
                        }
                        else {
                            parent.border.color = "#d2d2d2"
                        }
                    }
                    onClicked: {
                        boarderColorDialog.open()
                    }
                }
            }

            ComboBox {
                Layout.fillWidth: true
                Layout.fillHeight: true
                model: [ "Solid", "None" ]
                style: ComboBoxStyle {
                    background: Rectangle {
                        id: comboBack
                        height: 50
                        width: 150
                        color: "#f5f5f5"
                        border.width: 1
                        border.color: control.hovered ? "#1760c1" : "#d2d2d2"
                    }
                }
            }
        }

        Text {
            width: 220
            Layout.topMargin: 3
            color: "#4d4d75"
            font.pixelSize: 13
            font.family: "Microsoft Yahei UI"
            text: '填充颜色'
        }

        Rectangle {
            width: 50
            height: 50
            color: "#f0f2f3"
            border.width: 1
            border.color: "#d2d2d2"
            Rectangle {
                id: fillColorBlock
                width: 30
                height: 30
                color: "#c3c3c3"
                anchors.centerIn: parent
            }
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onContainsMouseChanged: {
                    if(containsMouse) {
                        parent.border.color = "#305ccc"
                    }
                    else {
                        parent.border.color = "#d2d2d2"
                    }
                }
                onClicked: {
                    fillColorDialog.open()
                }
            }
        }


    }
}
