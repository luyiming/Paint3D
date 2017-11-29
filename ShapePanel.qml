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
    property ParallelAnimation popupAnimation: popupAnimation
    property int instrument: DrawingBoard.INSTRUMENT_NONE
    property int opaqueness: opaquenessSlider.value
    property int thickness: thicknessSlider.value
    property color borderColor: boarderColorID.color
    property color fillColor: fillColorID.color
    property string borderStyle: borderStyle.currentText
    property string fillStyle: fillStyle.currentText

    onVisibleChanged: {
        if (visible) {
            titleAnimation.start()
            popupAnimation.start()
        }
    }

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

    ParallelAnimation {
        id: popupAnimation
        NumberAnimation {
            target: lines_and_curves
            property: "y"
            duration: 250
            easing.type: Easing.InOutQuad
            from: 10
            to: 0
        }
        NumberAnimation {
            target: lines_and_curves
            property: "opacity"
            duration: 250
            easing.type: Easing.InOutQuad
            from: 0
            to: 1
        }
        NumberAnimation {
            target: shapes
            property: "y"
            duration: 250
            easing.type: Easing.InOutQuad
            from: 10
            to: 0
        }
        NumberAnimation {
            target: shapes
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

        Item {
            width: 220
            height: 40
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
        }

        Text {
            width: 220
            color: "#4d4d75"
            font.pixelSize: 13
            font.family: "Microsoft Yahei UI"
            text: '2D 形状'
        }

        Item {
            width: 220
            height: 130
            Grid {
                id: shapes
                width: 220
                columns: 5
                spacing: 5

                property variant shapeIconName: ["circle", "capsule", "square", "rounded-square", "triangle",
                    "pentagon", "hexagon", "diamond", "right-triangle", "arrow",
                    "pointed-arrow", "arc", "five-pointed-star", "six-pointed-star", "four-pointed-star"]
                property variant shapeTitleName: ["圆形", "胶囊形(TODO)", "矩形", "圆角矩形", "三角形(TODO)",
                    "五边形(TODO)", "六边形(TODO)", "菱形(TODO)", "直角三角形(TODO)", "arrow(TODO)",
                    "pointed-arrow(TODO)", "圆弧(TODO)", "五角星(TODO)", "六角星(TODO)", "四角星(TODO)"]
                property variant shapeType: [DrawingBoard.SHAPE_CIRCLE, DrawingBoard.INSTRUMENT_NONE, DrawingBoard.SHAPE_SQUARE, DrawingBoard.SHAPE_ROUNDED_SQUARE, DrawingBoard.INSTRUMENT_NONE,
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
            boarderColorID.color = boarderColorDialog.color
        }
    }

    ColorDialog {
        id: fillColorDialog
        showAlphaChannel: true
        onAccepted: {
            fillColorID.color = fillColorDialog.color
        }
    }

    ColumnLayout {
        anchors.bottom: panel.bottom
        anchors.bottomMargin: 30
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
                    id: boarderColorID
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

            DropDownBox {
                id: borderStyle
                Layout.fillWidth: true
                Layout.fillHeight: true
                model: [ "Solid", "Dash", "Dot", "DashDot", "None" ]
                font.pointSize: 10
                font.family: "Microsoft Yahei UI"
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

        RowLayout{
            Rectangle {
                width: 50
                height: 50
                color: "#f0f2f3"
                border.width: 1
                border.color: "#d2d2d2"
                Rectangle {
                    id: fillColorID
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
            DropDownBox {
                id: fillStyle
                Layout.fillWidth: true
                Layout.fillHeight: true
                model: [ "Solid", "None" ]
                currentIndex: 1
                font.pointSize: 10
                font.family: "Microsoft Yahei UI"
            }
        }

    }
}
