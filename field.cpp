#include "field.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QBrush>

#include <QDebug>


Field::Field()
{
}


Figure *Field::get()
{
    return figure;
}

bool Field::isEmpty()
{
    return figure == nullptr;
}

bool Field::put(Figure *fig)
{
    if (isEmpty()) {
        figure = fig;
        return true;
    }
    else {
        return false;
    }
}

bool Field::remove(Figure *fig)
{
    if (figure == fig) {
        figure = nullptr;
        return true;
    }
    else {
        return false;
    }
}
