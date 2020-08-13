#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <QAbstractItemModel>
#include <vector>
#include <QString>

class GameBoard: public QAbstractItemModel {

    struct Element {
        QString color;
        QString number;
    };

    Q_OBJECT
    void enterListOfElement();
    int summary(std::vector<int> arr);
    std::vector<int> randoming();
    int emptyIndex;
    std::vector<Element> items;

public:
    enum GameBoardRoles {
        color = Qt::UserRole + 1,
        number
    };

    GameBoard();
    Q_INVOKABLE void move(int index);
    Q_INVOKABLE void shuffle();
    Q_INVOKABLE bool checkingGameOver();
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
};

#endif // GAMEBOARD_H
