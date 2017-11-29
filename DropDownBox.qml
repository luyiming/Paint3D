import QtQuick 2.0
import QtQuick.Controls 2.1

ComboBox {
    id: control
    model: ["Solid", "None"]

    delegate: ItemDelegate {
        width: control.width
        contentItem: Text {
            text: modelData
            color: "#4d4d75"
            font: control.font
            verticalAlignment: Text.AlignVCenter
        }
        highlighted: control.highlightedIndex === index
    }

    indicator: Canvas {
        id: canvas
        x: control.width - width - control.rightPadding
        y: control.topPadding + (control.availableHeight - height) / 2
        width: 12
        height: 8
        contextType: "2d"

        Connections {
            target: control
            onPressedChanged: canvas.requestPaint()
        }

        onPaint: {
            context.reset();
            context.moveTo(0, 0);
            context.lineTo(width, 0);
            context.lineTo(width / 2, height);
            context.closePath();
            context.fillStyle = "#676789";
            context.fill();
        }
    }

    background: Rectangle {
        implicitWidth: 150
        implicitHeight: 50
        color: "#f5f5f5"
        border.color: control.hovered ? "#1760c1" : "#d2d2d2"
        border.width: 1
        radius: 2
    }

    popup: Popup {
        y: control.height + 5
        width: control.width
        implicitHeight: contentItem.implicitHeight
        padding: 1

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: control.popup.visible ? control.delegateModel : null
            currentIndex: control.highlightedIndex

            ScrollIndicator.vertical: ScrollIndicator { }
        }

        background: Rectangle {
            border.color: "#0064b6"
            border.width: 1
            color: "#f5f5f5"
        }
    }
}
