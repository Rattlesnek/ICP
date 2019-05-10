#include "field.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QBrush>

#include <QDebug>


Field::Field(int _row, int _col) :
    row{_row}, col{_col}, figure{nullptr},
    topField{nullptr}, botField{nullptr}, rightField{nullptr}, leftField{nullptr}
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

Field *Field::getNext(Direction dir)
{
    switch (dir) {
        case topDir:
            return topField;
        case rightDir:
            return rightField;
        case botDir:
            return botField;
        case leftDir:
            return leftField;
        case topLeftDir:
            return topField->getNext(leftDir);
        case topRightDir:
            return topField->getNext(rightDir);
        case botLeftDir:
            return botField->getNext(leftDir);
        case botRightDir:
            return botField->getNext(rightDir);
    }
}
