#include "board.h"
#include "field.h"
#include <QDebug>

Board::Board()
{
    qDebug() << "start init";

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board.push_back(new Field(i + 1, j + 1));
        }
    }

    qDebug() << board.size();
    qDebug() << "load next";

    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            Field *f = getField(i, j);
            qDebug() << i << ' ' << j;
            f->topField = getField(i, j+1);
            qDebug() << "ok";
            f->botField = getField(i, j-1);
            qDebug() << "ok";
            f->rightField = getField(i+1, j);
            qDebug() << "ok";
            f->leftField = getField(i-1, j);
            qDebug() << "ok";
        }
    }

    qDebug() << "end init";
}

Field *Board::getField(int row, int col) {
    if (row < 1 || row > 8 || col < 1 || col > 8) {
        return nullptr;
    }
    qDebug() << "getField " << (row-1) * size + (col-1);



    return board[(row-1) * size + (col-1)];
}

//void Board::setInitialState()
//{

//}




