#ifndef BOARD_H
#define BOARD_H
#pragma once

#include <vector>

#include "field.h"

class Board
{
    static const int size = 8;
    std::vector<Field *> board;


public:
    Board();
    Field *getField(int row, int col);

};

#endif // BOARD_H
