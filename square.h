#ifndef SQUARE_H
#define SQUARE_H


#include <QObject>
#include <QColor>
#include <QBrush>
#include <QGraphicsRectItem>


class Square : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

    QBrush brush; // brush for the color of square
    bool white;   // true if the square is white
    bool active;  // true if the square is active (a figure is ready to move there)

public:
    static double size; // size of square


private:
    void setColor(QColor color);

public:
    Square(bool isWhite);
    void setOriginalColor(bool isWhite);
    void setActive(bool isActive, bool red);
    bool isActive();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void signalSquarePressed(bool active);

};


#endif // SQUARE_H
