import QtQuick 2.0
import QtQuick.Layouts 1.3

ColumnLayout {
    id: root
    width: 220

    property string title: 'Slider'
    property string postfixText: ''
    property int minimumValue: 1
    property int maximumValue: 100
    property int stepSize: 1
    property int value: 1

    RowLayout {
        Layout.preferredWidth: root.width
        Text {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
            color: "#4d4d75"
            font.pixelSize: 13
            font.family: "Microsoft Yahei UI"
            text: root.title
        }
        Rectangle {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
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
                text: slider.value + root.postfixText
                font.pixelSize: 13
                font.family: "Microsoft Yahei UI"
                color: '#757675'
            }
        }
    }
    BlueSlider {
        id: slider
        width: root.width
        minimumValue: root.minimumValue
        maximumValue: root.maximumValue
        stepSize: root.stepSize
        value: root.value
        onValueChanged: root.value = value
    }
}

