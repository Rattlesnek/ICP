/* Subject:  [ICP] The C++ Programming Language
 *
 * Author: Adam Pankuch (xpanku00.stud.fit.vutbr.cz)
 *         David Miksanik (xmiksa05.stud.fit.vutbr.cz)
 */

#include "square.h"

#include <QColor>
#include <QDebug>

// correct size - matches the size of figures
double Square::size = 62.5;

Square::Square(bool isWhite) :
    white{isWhite},
    active{false}
{
    // correct size - matches the size of figures
    setRect(0, 0, size, size);

    setOriginalColor(isWhite);
}

void Square::setOriginalColor(bool isWhite)
{
    if (isWhite == true) {
        setColor(Qt::white);
    }
    else {
        setColor(Qt::darkGray);
    }
}

void Square::setActive(bool isActive, bool red)
{
    active = isActive;

    if (isActive) {
        setColor(red ? Qt::red :Qt::blue );
    }
    else {
        setOriginalColor(white);
    }
}

bool Square::isActive()
{
    return active;
}


void Square::setColor(QColor _color)
{
    brush.setColor(_color);
    setBrush(_color);
}



void Square::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalSquarePressed(active);
}

