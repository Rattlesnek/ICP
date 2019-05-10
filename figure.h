#ifndef FIGURE_H
#define FIGURE_H
#pragma once

#include "fieldview.h"

class Field;

class Figure
{
protected:
    bool white;

public:
    Figure(bool isWhite);
    bool isWhite();
    virtual State getType() = 0;
    virtual bool checkMove(Field *from, Field *to) = 0;
    virtual ~Figure() = 0;
};



class King : public Figure
{
public:
    King(bool isWhite) : Figure(isWhite) {}
    State getType() { return (isWhite() ? wKing : bKing); }

    bool checkMove(Field *from, Field *to);
};


class Queen : public Figure
{
public:
    Queen(bool isWhite) : Figure(isWhite) {}
    State getType() { return (isWhite() ? wQueen : bQueen); }

    bool checkMove(Field *from, Field *to);
};


class Bishop : public Figure
{
public:
    Bishop(bool isWhite) : Figure(isWhite) {}
    State getType() { return (isWhite() ? wBishop : bBishop); }

    bool checkMove(Field *from, Field *to);
};


class Knight : public Figure
{
public:
    Knight(bool isWhite) : Figure(isWhite) {}
    State getType() { return (isWhite() ? wKnight : bKnight); }

    bool checkMove(Field *from, Field *to);
};


class Rook : public Figure
{
public:
    Rook(bool isWhite) : Figure(isWhite) {}
    State getType() { return (isWhite() ? wRook : bRook); }

    bool checkMove(Field *from, Field *to);
};


class Pawn : public Figure
{
public:
    Pawn(bool isWhite) : Figure(isWhite) {}
    State getType() { return (isWhite() ? wPawn : bPawn); }

    bool checkMove(Field *from, Field *to);
};

#endif // FIGURE_H
