#ifndef FIELD_H
#define FIELD_H

#include "figure.h"


class Field
{


    Figure *figure;

public:
    Field();

    Figure *get();
    bool isEmpty();
    bool put(Figure *fig);
    bool remove(Figure *fig);

};

#endif // FIELD_H
