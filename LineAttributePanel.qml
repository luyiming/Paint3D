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

    property ParallelAnimation popupAnimation: popupAnimation
    property int thickness: thicknessSlider.value
    property int opaqueness: opaquenessSlider.value
    property color brushColor: colorBlock.color

    function initPanel() {
        thicknessSlider.value = 1;
        opaquenessSlider.value = 100;
        colorBlock.color = "#000000";
    }

    ColorDialog {
        id: colorDialog
        showAlphaChannel: true
        onAccepted: {
            colorBlock.color = colorDialog.color
        }
    }

    ParallelAnimation {
        id: popupAnimation
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
        anchors.top: panel.top
        anchors.topMargin: 12
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 12

        Text {
            id: bigTitle
            width: 220
            color: "#0064b6"
            font.pixelSize: 18
            font.family: "Microsoft Yahei UI"
            text: '属性'
        }

        Text {
            width: 220
            Layout.topMargin: 3
            color: "#4d4d75"
            font.pixelSize: 13
            font.family: "Microsoft Yahei UI"
            text: qsTr("选择线的颜色")
        }

        Rectangle {
            id: colorButton
            width: 50
            height: 50
            color: "#f0f2f3"
            border.width: 1
            border.color: Qt.darker("#f0f2f3")
            Rectangle {
                id: colorBlock
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
                        parent.border.color = Qt.darker("#f0f2f3")
                    }
                }
                onClicked: {
                    colorDialog.open()
                }
            }
        }

        SliderWithBox {
            id: thicknessSlider
            Layout.topMargin: 10
            width: 220
            title: qsTr("粗细")
            postfixText: qsTr("像素")
            minimumValue: 1
            maximumValue: 100
            stepSize: 1
            value: 1
        }

        SliderWithBox {
            id: opaquenessSlider
            width: 220
            title: qsTr("不透明度")
            postfixText: '%'
            minimumValue: 1
            maximumValue: 100
            stepSize: 1
            value: 100
        }
    }
}
