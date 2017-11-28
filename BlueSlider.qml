import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4

Slider {
    id: slider
    implicitWidth: 220
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
