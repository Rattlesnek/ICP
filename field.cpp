/* Subject:  [ICP] The C++ Programming Language
 *
 * Author: Adam Pankuch (xpanku00.stud.fit.vutbr.cz)
 *         David Miksanik (xmiksa05.stud.fit.vutbr.cz)
 */

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


Figure *Field::getFig()
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

Figure *Field::moveFig(Field *to)
{
    // get figure from destination
    Figure *toFigure = to->getFig();
    // remove fig from dest
    to->remove(toFigure);

    // put fig to dest from this field
    to->put(figure);
    // remove fig from this field
    remove(figure);

    // returns nullptr or kicked figure from dest field
    return toFigure;
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
            if (topField == nullptr) return nullptr;
            return topField->getNext(leftDir);
        case topRightDir:
            if (topField == nullptr) return nullptr;
            return topField->getNext(rightDir);
        case botLeftDir:
            if (botField == nullptr) return nullptr;
            return botField->getNext(leftDir);
        case botRightDir:
            if (botField == nullptr) return nullptr;
            return botField->getNext(rightDir);
    }
}
