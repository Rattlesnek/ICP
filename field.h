#ifndef FIELD_H
#define FIELD_H

#include "figure.h"

enum Direction { topDir, topRightDir, rightDir, botRightDir, botDir, botLeftDir, leftDir, topLeftDir };

class Field
{

public:
    int row;
    int col;
    Figure *figure;

    Field *topField;
    Field *botField;
    Field *rightField;
    Field *leftField;

public:
    Field(int row, int col);

    Figure *getFig();
    bool isEmpty();
    bool put(Figure *fig);
    bool remove(Figure *fig);
    Field *getNext(Direction dir);

};

#endif // FIELD_H
