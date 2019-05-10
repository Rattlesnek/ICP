#include "board.h"
#include "field.h"
#include <QDebug>

#include "figure.h"

Board::Board()
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board.push_back(new Field(i + 1, j + 1));
        }
    }

    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            Field *f = getField(i, j);
            f->topField = getField(i+1, j);
            f->botField = getField(i-1, j);
            f->rightField = getField(i, j+1);
            f->leftField = getField(i, j-1);
        }
    }
}

Field *Board::getField(int row, int col) {
    if (row < 1 || row > 8 || col < 1 || col > 8) {
        return nullptr;
    }

    return board[(row-1) * size + (col-1)];
}

bool Board::moveFigure(Field *from, Field *to)
{

}

void Board::setInitialState()
{
    // init white
    for (int i = 1; i <= size; i++ ) {
        getField(2, i)->put(new Pawn(true));
    }
    getField(1, 1)->put(new Rook(true));
    getField(1, 2)->put(new Knight(true));
    getField(1, 3)->put(new Bishop(true));
    getField(1, 4)->put(new King(true));
    getField(1, 5)->put(new Queen(true));
    getField(1, 6)->put(new Bishop(true));
    getField(1, 7)->put(new Knight(true));
    getField(1, 8)->put(new Rook(true));

    getField(3, 5)->put(new King(true));

    // init black
    for (int i = 1; i <= size; i++ ) {
        getField(7, i)->put(new Pawn(false));
    }
    getField(8, 1)->put(new Rook(false));
    getField(8, 2)->put(new Knight(false));
    getField(8, 3)->put(new Bishop(false));
    getField(8, 4)->put(new King(false));
    getField(8, 5)->put(new Queen(false));
    getField(8, 6)->put(new Bishop(false));
    getField(8, 7)->put(new Knight(false));
    getField(8, 8)->put(new Rook(false));
}




