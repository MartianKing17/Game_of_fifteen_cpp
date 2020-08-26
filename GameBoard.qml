import QtQuick 2.0
import QtQuick.Window 2.14
import gameboard 1.0

GridView {
    id: _view
    interactive: false

    model: GameBoardModel {
        id: boardModel
    }

    delegate: Item {
        width: _view.cellWidth
        height: _view.cellHeight
        Tile {
            id: tile
            anchors.fill: parent
            color: model.color
            number: model.number
            border.color: "black"
            border.width: 1
            visible: model.number === "" ? false : true
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                _view.model.move(index);

                if(_view.model.checkingGameOver() === true) {
                    _menu.setDefWin(_view);
                    _view.visible = false;
                    _menu.visible = true;
                    _mix.visible = false;
                }
            }
        }
    }

    move: Transition {
        NumberAnimation { properties: "x,y"; duration: 400; easing.type: Easing.OutBounce }
    }
}


