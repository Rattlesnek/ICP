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

    Field *fieldReady;

public:
    Controller(BoardView *_boardView);
    void loadInitialState();
    void activatePossibleMoveFields(Figure *fig, Field *from);
    void deactivateAllFields();
    void applyStateOfField(Field *field);

public slots:
    void slotBoardViewPressed(int row, int col, bool active);
};

#endif // CONTROLLER_H
