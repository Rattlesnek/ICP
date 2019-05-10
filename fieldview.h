#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>

#include <vector>

#include "square.h"

// different states of a single FieldView
enum State { wKing, bKing, wQueen, bQueen, wRook, bRook, wBishop, bBishop, wKnight, bKnight, wPawn, bPawn, empty };


class FieldView : public QObject
{
    Q_OBJECT

    Square *square; // square in background
    QGraphicsPixmapItem *figurePixmap; // picture of figure

    State state; // state of FieldView
    int row;     // row where its located
    int col;     // col where its located

public:
    FieldView(int _row, int _col, bool isWhiteSquare);
    ~FieldView();

    void setPos(double x, double y);
    void addToScene(QGraphicsScene *scene);
    void setState(std::vector<QPixmap> &pixmaps, State _state);
    State getState();
    void setActive(bool active);

signals:
    void signalFieldViewPressed(int row, int col, bool active);

public slots:
    void slotSquarePressed(bool active);

};

#endif // FIELDVIEW_H
