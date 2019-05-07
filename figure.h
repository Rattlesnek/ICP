#ifndef FIGURE_H
#define FIGURE_H
#pragma once

class Field;

class Figure
{
    bool white;

public:
    Figure(bool isWhite);
    bool isWhite();
    bool checkMove(Field *from, Field *to);
};





class King : public Figure
{
public:
    bool checkMove(Field *from, Field *to);
};

class Queen : public Figure
{
public:
    bool checkMove(Field *from, Field *to);
};

class Bishop : public Figure
{
public:
    bool checkMove(Field *from, Field *to);
};

class Knight : public Figure
{
public:
    bool checkMove(Field *from, Field *to);
};

class Rook : public Figure
{
public:
    bool checkMove(Field *from, Field *to);
};

class Pawn : public Figure
{
public:
    bool checkMove(Field *from, Field *to);
};

#endif // FIGURE_H
