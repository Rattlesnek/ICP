#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <QObject>

#include <vector>

#include "board.h"
#include "boardview.h"

class Controller : public QObject
{
    Q_OBJECT

    Board board;
    BoardView *boardView;

public:
    Controller(BoardView *_boardView);

public slots:
    void slotFieldViewPressed(int row, int col, bool active);
};

#endif // CONTROLLER_H
