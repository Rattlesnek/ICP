#include "controller.h"

#include "figure.h"

#include <QDebug>

Controller::Controller(BoardView *_boardView, int _index, std::vector<LogList> &_log) :
    boardView{_boardView},
    fieldReady{nullptr},
    log{_log},
    index{_index}
{
    board.setInitialState();

    loadInitialState();
}

void Controller::loadInitialState()
{
    for (auto field : board.board) {
        Figure *fig = field->getFig();
        State state = empty;
        if (fig != nullptr) {
            state = fig->getType();
        }
        boardView->setStateFieldView(state, field->row, field->col);
    }
}

void Controller::activatePossibleMoveFields(Figure *fig, Field *from)
{
    for (int i = 1; i <= Board::size; i++) {
        for (int j = 1; j <= Board::size; j++) {

            if ( fig->checkMove(from, board.getField(i, j)) ) {
                boardView->setActiveFieldView(true, i, j);
            }
        }
    }
}

void Controller::deactivateAllFields()
{
    for (int i = 1; i <= Board::size; i++) {
        for (int j = 1; j <= Board::size; j++) {
            boardView->setActiveFieldView(false, i, j);
        }
    }
}

void Controller::applyStateOfField(Field *field)
{
    Figure *fig = field->getFig();
    if (fig != nullptr) {
        boardView->setStateFieldView(fig->getType(), field->row, field->col);
    }
    else {
        boardView->setStateFieldView(empty, field->row, field->col);
    }
}

void Controller::executeOperation(bool backward)
{
    LogList list = log[index];

    Field *from = board.getField(list.row_start, list.col_start);
    Field *to = board.getField(list.row_end, list.col_end);

    qDebug() << "from " << from->row << ' ' << from->col;
    qDebug() << "to " << to->row << ' ' << to->col;

    if (backward) {
        to->moveFig(from);

        //TODO delete the last line in text edit
        emit signalMoveDelete();
    }
    else {
        emit signalMoveWrite(from, to, empty); //print out

        from->moveFig(to);
    }

    applyStateOfField(to);
    applyStateOfField(from);
}

void Controller::addLog(State figure, int row_start, int col_start, int row_end, int col_end, State kick, State swap)
{
    if (index < log.size()) {
        log.erase(log.begin() + index, log.end());
    }

    // if index points to the end of loglist then normally add new loglist and increment index
    log.push_back(LogList(figure, row_start, col_start, row_end, col_end, kick, swap));
    index++;

    qDebug() << "size: " << log.size() << " index " << index;
}

bool Controller::back()
{
    deactivateAllFields();

    if (index-1 < 0) {
        return false;
    }
    else {
        index--;
        executeOperation(true);
        qDebug() << "size: " << log.size() << " back " << index;
        return true;
    }
}


bool Controller::next()
{
    qDebug() << "Next()";

    printLog();

    deactivateAllFields();

    if (index == log.size()) {
        return false;
    }
    else {
        executeOperation(false);
        index++;
        qDebug() << "size: " << log.size() << " next " << index;
        return true;
    }

    qDebug() << "... end";

}

void Controller::reset()
{
    deactivateAllFields();
    board.setInitialState();
    loadInitialState();

    index = 0;
    log.clear();

    fieldReady = nullptr;
}


void Controller::slotBoardViewPressed(int row, int col, bool active)
{
    qDebug() << "signal from BoardView recv in Controller " << row << " " << col << " " << active;

    // if clicked on figure
    Field *field = board.getField(row, col);
    Figure *fig = field->getFig();

    if (fieldReady == nullptr) {
        // no field is ready to move
        if (fig != nullptr) {
            // store field that is ready -- figure is ready to move
            fieldReady = field;
            // activate all possible fieldviews -- turn on red
            activatePossibleMoveFields(fig, field);
        }
    }
    else {
        // fieldReady is ready to move

        if (active) { // TODO should it be like this ???????
            // player clicked on active field

            // deactivate all fieldviews -- turn off red
            deactivateAllFields();

            State movedFigType = fieldReady->getFig()->getType();
            State kickedFigType = empty;

            // move figure
            Figure *kickedFig = fieldReady->moveFig(field);
            if (kickedFig != nullptr) {
                // delete kicked figure
                kickedFigType = kickedFig->getType();
                delete kickedFig; // TODO it should be stored somewhere
            }
            applyStateOfField(fieldReady);
            applyStateOfField(field);


            addLog(movedFigType, fieldReady->row, fieldReady->col, field->row, field->col, kickedFigType, empty);


            // field moved and now there is none
            fieldReady = nullptr;
        }
        else {
            // player clicked on non active field

            // deactivate all fieldviews -- turn off red
            deactivateAllFields();

            fieldReady = nullptr;
        }
    }    
}

void Controller::printLog()
{
    for (auto it : log)
    {
        qDebug() << it.col_start << it.row_start << it.col_end << it.row_start;
    }
}
