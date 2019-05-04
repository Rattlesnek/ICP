#include "field.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QBrush>

#include <QDebug>


Field::Field()
{
}


void Field::setImage()
{
    picture = new QGraphicsPixmapItem();
    picture->setPixmap(QPixmap("pawn1.png"));
    picture->show();
}

void Field::setRect()
{
    rect = new QGraphicsRectItem();
    rect->setRect(0, 0, 60, 60);
    rect->show();
}

void Field::setPos(int x, int y)
{
    picture->setPos(x, y);
    rect->setPos(x, y);
}

void Field::addToScene(QGraphicsScene *scene)
{
    scene->addItem(picture);
    scene->addItem(rect);
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


void Field::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "pressed";
}


//void Field::setColor(QColor color)
//{
//    brush.setColor(color);
//    setBrush(color);
//}
