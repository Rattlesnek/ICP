#ifndef FIGURE_H
#define FIGURE_H
#pragma once

#include "fieldview.h"

class Field;

/**
 * @brief The Figure class represents backend figure
 */
class Figure
{
protected:
    /**
     * @brief checkMoveBishop method which checks move from field "from" to field "to"
     * @param from start position
     * @param to end position
     * @return true if the move is possible, false otherwise
     */
    bool checkMoveBishop(Field *from, Field *to);
    /**
     * @brief checkMoveRook method which checks move from field "from" to field "to"
     * @param from start position
     * @param to end position
     * @return true if the move is possible, false otherwise
     */
    bool checkMoveRook(Field *from, Field *to);

    bool white; // whether the figure is white

public:
    /**
     * @brief Figure constructor
     * @param isWhite whether the figure should be white
     */
    Figure(bool isWhite);
    /**
     * @brief isWhite method checks whether figure is white
     * @return true if figure is white, false if its black
     */
    bool isWhite();

    /**
     * @brief getType virtual method which gets the type of the figure
     * @return type of the figure
     */
    virtual State getType() = 0;
    /**
     * @brief checkMove virtual method which checks move from field "from" to field "to"
     * @param from field where the figure is currently
     * @param to field where the figure is going to move
     * @return true if the move is possible, false otherwise
     */
    virtual bool checkMove(Field *from, Field *to) = 0;
    virtual ~Figure() = 0;
};


/**
 * @brief The King class represents the backend King
 */
class King : public Figure
{
public:
    /**
     * @brief King contructor
     * @param isWhite
     */
    King(bool isWhite) : Figure(isWhite) {}
    /**
     * @brief getType definition of virtual method from Figure which gets the type of the figure
     * @return type of the figure
     */
    State getType() { return (isWhite() ? wKing : bKing); }

    /**
     * @brief checkMove definition of virtual method from Figure which checks move from field "from" to field "to"
     * @param from field where the figure is currently
     * @param to field where the figure is going to move
     * @return true if the move is possible, false otherwise
     */
    bool checkMove(Field *from, Field *to);
};

/**
 * @brief The Queen class represents the backend Queen
 */
class Queen : public Figure
{
public:
    /**
     * @brief Queen constructor
     * @param isWhite
     */
    Queen(bool isWhite) : Figure(isWhite) {}
    /**
     * @brief getType definition of virtual method from Figure which gets the type of the figure
     * @return type of the figure
     */
    State getType() { return (isWhite() ? wQueen : bQueen); }

    /**
     * @brief checkMove definition of virtual method from Figure which checks move from field "from" to field "to"
     * @param from field where the figure is currently
     * @param to field where the figure is going to move
     * @return true if the move is possible, false otherwise
     */
    bool checkMove(Field *from, Field *to);
};

/**
 * @brief The Bishop class represents the backend Bishop
 */
class Bishop : public Figure
{
public:
    /**
     * @brief Bishop constructor
     * @param isWhite
     */
    Bishop(bool isWhite) : Figure(isWhite) {}
    /**
     * @brief getType definition of virtual method from Figure which gets the type of the figure
     * @return type of the figure
     */
    State getType() { return (isWhite() ? wBishop : bBishop); }

    /**
     * @brief checkMove definition of virtual method from Figure which checks move from field "from" to field "to"
     * @param from field where the figure is currently
     * @param to field where the figure is going to move
     * @return true if the move is possible, false otherwise
     */
    bool checkMove(Field *from, Field *to);
};

/**
 * @brief The Knight class represents the backend Knight
 */
class Knight : public Figure
{
public:
    /**
     * @brief Knight constructor
     * @param isWhite
     */
    Knight(bool isWhite) : Figure(isWhite) {}
    /**
     * @brief getType definition of virtual method from Figure which gets the type of the figure
     * @return type of the figure
     */
    State getType() { return (isWhite() ? wKnight : bKnight); }

    /**
     * @brief checkMove definition of virtual method from Figure which checks move from field "from" to field "to"
     * @param from field where the figure is currently
     * @param to field where the figure is going to move
     * @return true if the move is possible, false otherwise
     */
    bool checkMove(Field *from, Field *to);
};

/**
 * @brief The Rook class represents the backend Rook
 */
class Rook : public Figure
{
public:
    /**
     * @brief Rook constructor
     * @param isWhite
     */
    Rook(bool isWhite) : Figure(isWhite) {}
    /**
     * @brief getType definition of virtual method from Figure which gets the type of the figure
     * @return type of the figure
     */
    State getType() { return (isWhite() ? wRook : bRook); }

    /**
     * @brief checkMove definition of virtual method from Figure which checks move from field "from" to field "to"
     * @param from field where the figure is currently
     * @param to field where the figure is going to move
     * @return true if the move is possible, false otherwise
     */
    bool checkMove(Field *from, Field *to);
};

/**
 * @brief The Pawn class represents the backend Pawn
 */
class Pawn : public Figure
{
public:
    /**
     * @brief Pawn contructor
     * @param isWhite
     */
    Pawn(bool isWhite) : Figure(isWhite) {}
    /**
     * @brief getType definition of virtual method from Figure which gets the type of the figure
     * @return type of the figure
     */
    State getType() { return (isWhite() ? wPawn : bPawn); }

    /**
     * @brief checkMove definition of virtual method from Figure which checks move from field "from" to field "to"
     * @param from field where the figure is currently
     * @param to field where the figure is going to move
     * @return true if the move is possible, false otherwise
     */
    bool checkMove(Field *from, Field *to);
};

#endif // FIGURE_H
