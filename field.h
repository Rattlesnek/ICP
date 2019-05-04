#ifndef FIELD_H
#define FIELD_H
#pragma once

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QBrush>

#include "figure.h"


class Field
{
    QBrush brush;
    QGraphicsPixmapItem *picture;
    QGraphicsRectItem *rect;

    Figure *figure;

public:
    Field();
    void setImage();
    void setRect();
    void setPos(int x, int y);
    void addToScene(QGraphicsScene *scene);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setColor(QColor color);


    Figure *get();
    bool isEmpty();
    bool put(Figure *fig);
    bool remove(Figure *fig);

};

#endif // FIELD_H
