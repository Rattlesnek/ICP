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

#endif // FIGURE_H
