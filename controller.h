#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <QObject>

#include <vector>

#include "board.h"
#include "boardview.h"
#include "loglist.h"


class Controller : public QObject
{
    Q_OBJECT

    Board board;
    BoardView *boardView;
    Field *fieldReady;

    std::vector<LogList> log; //sequenction of steps
    int index;

public:
    Controller(BoardView *_boardView, int _index, std::vector<LogList> &_log);
    void loadInitialState();
    void activatePossibleMoveFields(Figure *fig, Field *from);
    void deactivateAllFields();
    void applyStateOfField(Field *field);
    Figure *figureFactory(State state);

    bool whiteOnMove();
    void executeOperation(bool backward);
    Field *findFieldOfMovedFigure(State type, Field *to);

    void addLog(State figure, int x_start, int y_start,
                int x_end, int y_end, State kick, State swap);
    void deleteFollowingLogs();

    bool back();
    bool next();
    void reset();

    void printLog();
    void errorMessage(QString error);

    bool kingCheck(bool isWhite);

public slots:
    void slotBoardViewPressed(int row, int col, bool active);

signals:
    void signalMoveWrite(Field *from, Field *to, State swap);
    void signalMoveDelete();
};

#endif // CONTROLLER_H
