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
    property variant vectorModel: []


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
            text: qsTr("矢量图形")
        }

        ExclusiveGroup { id: shapeGroup }

        Text {
            width: 220
            Layout.topMargin: 3
            color: "#4d4d75"
            font.pixelSize: 13
            font.family: "Microsoft Yahei UI"
            text: qsTr("直线和曲线")
        }

        Item {
            width: 220
            height: 40
            Row {
                id: lines_and_curves
                width: 220

                property variant shapeIconName: ["line", "curve2", "curve3", "curve4"]
                property variant shapeTitleName: [qsTr("直线"), qsTr("两点曲线(TODO)"), qsTr("三点曲线(TODO)"), qsTr("四点曲线(TODO)")]
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
            text: qsTr("2D 形状")
        }

        Item {
            width: 220
            height: 40
            Grid {
                id: shapes
                width: 220
                columns: 5
                spacing: 5

                property variant shapeIconName: ["circle", "square", "polygon"]
                property variant shapeTitleName: [qsTr("圆形"), qsTr("矩形"), qsTr("多边形")]
                property variant shapeType: [DrawingBoard.SHAPE_CIRCLE, DrawingBoard.SHAPE_SQUARE, DrawingBoard.VECTOR_POLYGON]

                Repeater {
                    model: 3

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
                            }
                        }
                    }
                }
            }
        }

        Rectangle {
            color: "white"
            border.color: "blue"
            width: 220; height: 200

            ListView {
                id: listView
                width: 218; height: 198
                anchors.centerIn: parent

                model: vectorModel
                delegate: Component {
                    Item {
                        width: 220; height: 30
                        Text {
                            anchors.centerIn: parent
//                            anchors.horizontalCenterOffset: -70
                            text: modelData
                            font.pixelSize: 15
                            font.family: "Microsoft Yahei UI"
                            color: "#4d4d75"
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: listView.currentIndex = index
                        }
                    }
                }
                highlight: Rectangle {
                    color: "lightsteelblue"
                }
                focus: true
                clip: true
                onCurrentIndexChanged: console.log(currentIndex)
            }
        }

    }
}
