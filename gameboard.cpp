#include "gameboard.h"
#include <iostream>
#include <random>
#include <array>

GameBoard::GameBoard() : QAbstractItemModel() {
    enterListOfElement();
}

QHash<int, QByteArray> GameBoard::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[color] = "color";
    roles[number] = "number";
    return roles;
}

QVariant GameBoard::data(const QModelIndex &index, int role = Qt::DisplayRole) const {

    if (!index.isValid()) {
        return QVariant();
    }

    int row = index.row();

    switch (role) {
    case color:
        return QVariant(items.at(row).color);
    case number:
        return QVariant(items.at(row).number);
    default:
        break;
    }

    return QVariant();
}

QModelIndex GameBoard::parent(const QModelIndex &child) const {

    return QModelIndex();
}

QModelIndex GameBoard::index(int row, int column, const QModelIndex &parent) const {

    Element element = items.at(row);
    return createIndex(row, column, &element);
}

int GameBoard::columnCount(const QModelIndex &parent) const {
    return parent.column();
}

int GameBoard::rowCount(const QModelIndex &parent = QModelIndex()) const {

    return this->items.size();
}

std::vector<int> GameBoard::randoming() {
    const std::size_t len = 16;
    std::vector<int> arr;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, int(len - 1));

    bool isAvailable = false;

    while (arr.size() < len) {
        int number = distribution(generator);

        for (const int &elem : arr) {

            if (elem == number) {
                isAvailable = true;
                break;
            }
        }

        if (isAvailable) {
            isAvailable = false;
            continue;
        }

        arr.push_back(number);
    }
    return arr;
}

int GameBoard::summary(std::vector<int> arr) {
    int sum = 0;
    std::vector<int> copyArr;

    for (std::size_t i = 0; i < arr.size(); ++i) {

        if (arr.at(i) == 0) {
            sum += i + 1;
            continue;
        }

        copyArr.push_back(arr[i]);
    }

    for (std::size_t i = 0; i < copyArr.size() - 1; ++i) {

        if (copyArr.at(i) > copyArr.at(i+1)) {
            continue;
        }

        ++sum;
    }

    return sum;
}

void GameBoard::enterListOfElement() {
    const std::size_t lenOfColorArray = 3;
    QString color[lenOfColorArray] = {"#FF0000", "#00BFFF", "#9ACD32"};
    const std::size_t len = 16;

    std::vector<int> arr;
    int sum = 1;

    while (sum % 2) {
        arr = randoming();
        sum = summary(arr);
    }

    if (this->items.size() > 0) {
        this->items.clear();
    }

    beginInsertRows(QModelIndex(), this->items.size(), this->items.size());

    for (std::size_t i = 0, j = 0; i < len; ++i, ++j) {

        if (j > 2) {
            j = 0;
        }

        if (arr.at(i) == 0) {
            items.push_back({"", ""});
            emptyIndex = i;
            continue;
        }

        items.push_back({color[j], QString().setNum( arr.at(i) )});
    }

    endInsertRows();
}

void GameBoard::move(int index) {
    int horizontal = index < emptyIndex ? 1 : 0;
    int vertical = index < emptyIndex ? 0 : 1;

    auto checkIndexing = [](int firstIndex, int secondIndex) {
        return (std::abs(firstIndex - secondIndex) == 1) || (std::abs(firstIndex - secondIndex) == 4);
    };

    if (checkIndexing(emptyIndex, index)) {
        if (std::abs(emptyIndex - index) == 1) {
            beginMoveRows(QModelIndex(),index,index,QModelIndex(), emptyIndex + horizontal);
        } else if (std::abs(emptyIndex - index) == 4) {
            beginMoveRows(QModelIndex(),index,index,QModelIndex(),emptyIndex);
            endMoveRows();
            beginMoveRows(QModelIndex(), emptyIndex + vertical, emptyIndex + vertical, QModelIndex(), index + vertical);
        }

        emptyIndex = index;
        endMoveRows();
    }
}

bool GameBoard::checkingGameOver() {

    for (std::size_t i = 0; i < items.size(); ++i) {
        if ( QString ( items.at(i).number ).toUInt() != i + 1) {
            return false;
        }
    }

    return true;
}

void GameBoard::shuffle() {
    beginResetModel();
    enterListOfElement();
    endResetModel();
}

