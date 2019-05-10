#include "fieldview.h"

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QDebug>

#include <vector>


FieldView::FieldView(int _row, int _col, bool isWhiteSquare) :
    square{new Square(isWhiteSquare)},
    figurePixmap{new QGraphicsPixmapItem()},
    state{empty},
    row{_row}, col{_col}
{
    // show square
    square->show();

    // connect signal from Square to the slot in FieldView (enable re-sending of signal)
    connect(square, &Square::signalSquarePressed, this, &FieldView::slotSquarePressed);
}

FieldView::~FieldView()
{
    delete square;
    delete figurePixmap;
}

void FieldView::setPos(double x, double y)
{
    square->setPos(x, y);
    figurePixmap->setPos(x, y);
}

void FieldView::addToScene(QGraphicsScene *scene)
{
    scene->addItem(square);
    scene->addItem(figurePixmap);
}

void FieldView::setState(std::vector<QPixmap> &pixmaps, State new_state)
{
    if (state == empty) {
        if (new_state == empty) {
            ;
        }
        else {
            figurePixmap->setPixmap(pixmaps[new_state]);
            figurePixmap->show();
        }
    }
    else {
        if (new_state == empty) {
            figurePixmap->hide();
        }
        else {
            figurePixmap->setPixmap(pixmaps[new_state]);
        }
    }
    state = new_state;
}

State FieldView::getState()
{
    return state;
}

void FieldView::setActive(bool active)
{
    square->setActive(active);
}

void FieldView::slotSquarePressed(bool active)
{
    // re-send signal with information about row and col
    emit signalFieldViewPressed(row, col, active);
}
