import QtQuick 2.0
import QtQuick.Window 2.14
import gameboard 1.0

GridView {
    id: view
    interactive: false

    model: GameBoardModel {
        id: boardModel
    }

    delegate: Item {
        width: view.cellWidth
        height: view.cellHeight
        Tile {
            id: tile
            color: model.number === "" ? "white" : model.color
            width: view.cellWidth
            height: view.cellHeight
            number: model.number
            border.color: "black"
            border.width: 1
            visible: model.number === "" ? false : true
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                view.model.move(index);

                if (view.model.checkingGameOver() === true) {
                    menu.setDefWin(view);
                    view.visible = false;
                    menu.visible = true;
                    mix.visible = false;
                }
            }
        }

    }

    move: Transition {
        NumberAnimation { properties: "x,y"; duration: 400; easing.type: Easing.OutBounce }
    }
}


