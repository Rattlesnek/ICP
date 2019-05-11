#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QObject>
#include <QPixmap>
#include <QDebug>
#include <QGraphicsScene>

#include <vector>

#include "fieldview.h"

class BoardView : public QObject
{
    Q_OBJECT

    std::vector<QPixmap> pixmaps; // vector of pixmaps of figures
    std::vector<FieldView *> fieldviews; // vector of fields

public:
    BoardView(QGraphicsScene *scene);
    void preparePixmaps();
    void createBoard(QGraphicsScene *scene, double shift_down, double shift_right);
    FieldView *getFieldView(int row, int col);
    void setActiveFieldView(bool active, bool red, int row, int col);
    void setStateFieldView(State state, int row, int col);

signals:
    void signalBoardViewPressed(int row, int col, bool active);

public slots:
    void slotFieldViewPressed(int row, int col, bool active);
};

#endif // BOARDVIEW_H
