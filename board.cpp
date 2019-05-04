#include "board.h"
#include "field.h"
#include <QDebug>

Board::Board() :
    board{size * size}
{
    for (int i = 0; i < size * size; i++) {
        board[i] = new Field();
    }
}

Field *Board::getField(int row, int col) {
    return board[row * size + col];
}




