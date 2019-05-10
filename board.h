#ifndef BOARD_H
#define BOARD_H
#pragma once

#include <vector>

#include "field.h"

class Board
{
public:
    static const int size = 8;
    std::vector<Field *> board;

public:
    class OutOfBoard {};

    Board();
    Field *getField(int row, int col);
    void setInitialState();

//    void checkAllMoves(Field *from);

};

#endif // BOARD_H
