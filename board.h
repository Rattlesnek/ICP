#ifndef BOARD_H
#define BOARD_H
#pragma once

#include <vector>

#include "field.h"

/**
 * @brief The Board class represents backend board
 */
class Board
{
public:
    static const int size = 8; // size of board
    std::vector<Field *> board; // vector of Fields - board

public:
    /**
     * @brief Board contructor
     */
    Board();
    /**
     * @brief getField method returns a Field instance from given location
     * @param row location row
     * @param col location col
     * @return Field instance or nullptr if there is no such
     */
    Field *getField(int row, int col);

    /**
     * @brief getField method return a Field contain Figure with given State
     *         if the are more then one figure with same State,
     *         then function return the first figurn from bot to top and left to right
     * @param s type of figure
     * @return Field instance or nullptr if there is no such
     */
    Field *getField(State s);
    /**
     * @brief setInitialState method sets the initial location of figures on the board
     */
    void setInitialState();
    /**
     * @brief clearBoard method removes all figures from the board
     */
    void clearBoard();
};

#endif // BOARD_H
