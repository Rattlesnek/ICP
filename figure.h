#ifndef FIGURE_H
#define FIGURE_H
#pragma once

class Field;

class Figure
{
    bool white;

public:
    Figure(bool isWhite);
    bool move(Field field);
};

class King : Figure
{

};

class Queen : Figure
{

};

class Bishop : Figure
{

};

class Knight : Figure
{

};

class Rook : Figure
{

};

class Pawn : Figure
{

};

#endif // FIGURE_H
