import QtQuick 2.9
import QtQuick.Controls 1.2

Rectangle {
    property var number: 0

    FontMetrics {
        id: fontMetrics
    }

    Text {
        anchors.centerIn: parent
        text: number
        font.pixelSize: Math.min(parent.width, parent.height) / 2
    }
}
