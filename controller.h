/* Subject:  [ICP] The C++ Programming Language
 *
 * Author: Adam Pankuch (xpanku00.stud.fit.vutbr.cz)
 *         David Miksanik (xmiksa05.stud.fit.vutbr.cz)
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <QObject>

#include <vector>

#include "board.h"
#include "boardview.h"
#include "loglist.h"

/**
 * @brief The Controller class represents the main part and logic of the whole program
 */
class Controller : public QObject
{
    Q_OBJECT

    Board board; // backend board
    BoardView *boardView; // frontend board
    Field *fieldReady; // temporary backend field which is "ready to move"

    std::vector<LogList> log; // record of steps
    int index; // current index in the log

public:
    /**
     * @brief Controller constructor
     * @param _boardView pointer to the frontend board
     * @param _index initial index in the log
     * @param _log record of steps
     */
    Controller(BoardView *_boardView, int _index, std::vector<LogList> &_log);
    /**
     * @brief loadInitialState method loads initial state of the backend board to the frontend board
     */
    void loadInitialState();
    /**
     * @brief activatePossibleMoveFields method sets frontend fields to "active" according to backend board
     * @param fig backend figure which moves
     * @param from backend field from which the figure moves
     */
    void activatePossibleMoveFields(Figure *fig, Field *from);
    /**
     * @brief deactivateAllFields method sets all frontend fields to "not active"
     */
    void deactivateAllFields();
    /**
     * @brief applyStateOfField method sets state of a single frontend field according to the backend field
     * @param field backend field
     */
    void applyStateOfField(Field *field);
    /**
     * @brief figureFactory method creates a backend figure according to given type of figure
     * @param state type of figure
     * @return Figure instance
     */
    Figure *figureFactory(State state);

    /**
     * @brief whiteOnMove method checks whether the white is on move
     * @return true if white is on move, false if black is on move
     */
    bool whiteOnMove();
    /**
     * @brief executeOperation method executes either "next" or "back" operation
     * @param backward true if "back", false if "next"
     */
    void executeOperation(bool backward);
    /**
     * @brief findFieldOfMovedFigure methods finds the "source field" of the figure which moved to the "destination field"
     * @param type type of the figure
     * @param to backend destination field
     * @return backend source field
     */
    Field *findFieldOfMovedFigure(State type, Field *to);

    /**
     * @brief addLog method adds log to the log vector
     * @param figure
     * @param x_start
     * @param y_start
     * @param x_end
     * @param y_end
     * @param kick
     * @param swap
     */
    void addLog(State figure, int x_start, int y_start,
                int x_end, int y_end, State kick, State swap);
    /**
     * @brief deleteFollowingLogs method deletes all logs that follow after current and including current
     */
    void deleteFollowingLogs();

    /**
     * @brief back method executes back operation
     * @return true if succesful
     */
    bool back();
    /**
     * @brief next method executes next operation
     * @return true if succesful
     */
    bool next();
    /**
     * @brief reset method executes reset operation
     */
    void reset();

    /**
     * @brief printLog debug print of log vector on qDebug()
     */
    void printLog();
    /**
     * @brief errorMessage method shows modal dialog with error
     * @param string error string
     */
    void errorMessage(QString string);

    /**
     * @brief kingCheck answers of this question: is king in check?
     * @param isWhite if is true then check white king else check black king
     * @return true if is check
     */
    bool kingCheck(bool isWhite);
    /**
     * @brief kingMate answers of this question: is king in mate?
     * @param isWhite if is true then check white king else check black king
     * @return true if is mate
     */
    bool kingMate(bool isWhite);
    /**
     * @brief isStillCheck if is still check if king move in given direction
     * @param king position of king
     * @param isWhite if is true then check white king else check black king
     * @param dir move of king
     * @return bool true if is still king in check
     */
    bool isStillCheck(Field *king, bool isWhite, Direction dir);

public slots:
    /**
     * @brief slotBoardViewPressed slot which receives signal from frontend board that mouse clicked on it
     * @param row location row
     * @param col location col
     * @param active whether the frontend field was active
     */
    void slotBoardViewPressed(int row, int col, bool active);

signals:
    /**
     * @brief signalMoveWrite signal emited when move is done
     * @param from start position of move
     * @param to end position of move
     * @param swap type swapped figure, empty if no swapped
     * @param check if move caused check or mate (0 - no; 1 - check; 2 - mate)
     */
    void signalMoveWrite(Field *from, Field *to, State swap, int check);
    /**
     * @brief signalCheckKing signal emmited after move
     * @param check (0 - no; 1 - check; 2 - mate)
     * @param isWhite true then white player played
     */
    void signalCheckKing(int check, bool isWhite);
    /**
     * @brief signalMoveDelete
     */
    void signalMoveDelete(int, std::vector<LogList>);
    /**
     * @brief signalMarkRow signal emiited if is needed update current position in logs table
     * @param row number of row
     */
    void signalMarkRow(int row);
};

#endif // CONTROLLER_H
