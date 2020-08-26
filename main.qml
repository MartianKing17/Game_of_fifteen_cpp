import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 1.5
import gameboard 1.0

Window {
    id: _mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Game of fifteen")
    property int tileHeight: height / 5
    property int tileWidth: width / 4

    signal signalEnteringElement;
    signal mixVisibility;
    onSignalEnteringElement: enterListOfElement()
    onMixVisibility: _mix.visible = true

    OverGameMenu {
        id: _menu
        visible: false
        anchors.fill: parent
    }

    GameBoard {
        id: _view
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        width: parent.width
        height: tileHeight * 4
        cellHeight: tileHeight
        cellWidth: tileWidth
    }

    Button {
        id: _mix
        text: "Mix"
        width: parent.width
        height: parent.height - tileHeight * 4
        anchors.top: _view.bottom
        onClicked: _view.model.shuffle()
    }
}
