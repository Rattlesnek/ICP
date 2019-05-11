#include "controller.h"

#include "figure.h"

#include <QDebug>
#include <QMessageBox>

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
                boardView->setActiveFieldView(true, true, i, j);
            }
        }
    }
}

void Controller::deactivateAllFields()
{
    for (int i = 1; i <= Board::size; i++) {
        for (int j = 1; j <= Board::size; j++) {
            boardView->setActiveFieldView(false, false, i, j);
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

Figure *Controller::figureFactory(State state)
{
    switch (state) {
        case wKing:
            return new King(true);
        case bKing:
            return new King(false);
        case wQueen:
            return new Queen(true);
        case bQueen:
            return new Queen(false);
        case wBishop:
            return new Bishop(true);
        case bBishop:
            return new Bishop(false);
        case wKnight:
            return new Knight(true);
        case bKnight:
            return new Knight(false);
        case wRook:
            return new Rook(true);
        case bRook:
            return new Rook(false);
        case wPawn:
            return new Pawn(true);
        case bPawn:
            return new Pawn(false);
        case empty:
            return nullptr;
    }
}

bool Controller::whiteOnMove()
{
    return index % 2 == 0;
}

void Controller::executeOperation(bool backward)
{
    bool player = whiteOnMove();
    LogList &list = log[index];

    Field *from;
    Field *to = board.getField(list.row_end, list.col_end);

    if (list.row_start != 0 && list.col_start != 0) {
        // long notation
        from = board.getField(list.row_start, list.col_start);
    }
    else {
        // short notation
        from = findFieldOfMovedFigure(list.figure, to);
        if (from == nullptr) {
            deleteFollowingLogs();
            qDebug() << "INCORECT RECORD - SHORT NOTATION";
            errorMessage("Incorrect record!");
            return;
        }
        list.row_start = from->row;
        list.col_start = from->col;
    }


    qDebug() << "from " << from->row << ' ' << from->col;
    qDebug() << "to " << to->row << ' ' << to->col;

    if (backward) {
        // BACKWARD
        emit signalMoveDelete(); //delete last line

        // also solves when no fig was kicked
        Figure *kickedFig = figureFactory(list.kick);
        to->moveFig(from);
        to->put(kickedFig);

        if (list.swap != empty) {
            qDebug() << "swap!";
            Figure *movedFig = from->getFig();
            Figure *swapedFig = figureFactory(list.figure);
            from->remove(movedFig);
            delete movedFig;
            from->put(swapedFig);
        }
    }
    else {
        // FORWARD
        Figure *movedFig = from->getFig();
        // check if the move is possible
        if (movedFig != nullptr && movedFig->getType() == list.figure && // check if there is figure of given type
                (( movedFig->isWhite() && whiteOnMove() ) || ( ! movedFig->isWhite() && ! whiteOnMove() )) && // check if the correct player is on move
                movedFig->checkMove(from, to) ) { // check if the move can be done
            ; // correct
        }
        else {
            // incorect record
            deleteFollowingLogs();
            qDebug() << "INCORECT RECORD";
            errorMessage("Incorrect record!");
            return;
        }

        emit signalMoveWrite(from, to, empty, 0); //print out

        Figure *kickedFig = from->moveFig(to);
        if (kickedFig != nullptr) {
            list.kick = kickedFig->getType();
            delete kickedFig;
        }

        if (list.swap != empty) {
            Figure *swapFig = figureFactory(list.swap);
            to->remove(movedFig);
            delete movedFig;
            to->put(swapFig);
        }

        int check = 0;
        if (kingCheck(!player))
        {
            check = 1;
            if (kingMate(!player))
                check = 2;
        }
        emit signalCheckKing(check);
    }

    applyStateOfField(to);
    applyStateOfField(from);

}

Field *Controller::findFieldOfMovedFigure(State type, Field *to)
{
    for (int i = 1; i <= Board::size; i++) {
        for (int j = 1; j <= Board::size; j++) {
            Field *from = board.getField(i, j);
            Figure *fig = from->getFig();
            if (fig != nullptr && fig->getType() == type  &&
                    (( fig->isWhite() && whiteOnMove() ) || ( ! fig->isWhite() && ! whiteOnMove() )) &&
                    fig->checkMove(from, to) ) {
                return from;
            }
        }
    }
    return nullptr;
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

    if (kingCheck(true)) //true --- white plays
        qDebug() << "WHITE: check";
}

void Controller::deleteFollowingLogs()
{
    log.erase(log.begin() + index, log.end());
    index--;
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
    bool player = whiteOnMove();
    qDebug() << "signal from BoardView recv in Controller " << row << " " << col << " " << active;

    // if clicked on figure
    Field *field = board.getField(row, col);
    Figure *fig = field->getFig();

    if (fieldReady == nullptr) {
        // no field is ready to move
        if (fig != nullptr && (( fig->isWhite() && whiteOnMove() ) || ( ! fig->isWhite() && ! whiteOnMove() )) ) {
            // store field that is ready -- figure is ready to move
            fieldReady = field;

            boardView->setActiveFieldView(true, false, fieldReady->row, fieldReady->col);
            // activate all possible fieldviews -- turn on red
            activatePossibleMoveFields(fig, field);
        }
    }
    else {
        // fieldReady is ready to move
        if (fieldReady->getFig()->checkMove(fieldReady, field)) {
            // player clicked on active field

            // deactivate all fieldviews -- turn off red
            deactivateAllFields();

            emit  signalMoveWrite(fieldReady, field, empty, 0);

            State movedFigType = fieldReady->getFig()->getType();
            State kickedFigType = empty;
            State swapFigType = empty;

            // move figure
            Figure *kickedFig = fieldReady->moveFig(field);
            if (kickedFig != nullptr) {
                // delete kicked figure
                kickedFigType = kickedFig->getType();
                delete kickedFig; // TODO it should be stored somewhere
            }

            // change pawn
            if ((movedFigType == wPawn && field->row == 8) || (movedFigType == bPawn && field->row == 1)) {
                Figure *swapFig = field->getFig();
                field->remove(swapFig);
                delete swapFig;

//                QString file = QInputDialog::getText(this, tr("Load"), tr("Enter name of file:"),
//                                                        QLineEdit::Normal, QString(), &ok);

                // TODO
                swapFig = new Queen(movedFigType == wPawn ? true : false);
                field->put(swapFig);
                swapFigType = swapFig->getType();
            }

            applyStateOfField(fieldReady);
            applyStateOfField(field);

            int check = 0;
            if (kingCheck(!player))
            {
                check = 1;
                if (kingMate(!player))
                    check = 2;
            }
            emit signalCheckKing(check);

            addLog(movedFigType, fieldReady->row, fieldReady->col, field->row, field->col, kickedFigType, swapFigType);


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

void Controller::errorMessage(QString error)
{
    QMessageBox messageBox;
    messageBox.critical(nullptr, "Error massage", error);
    messageBox.setFixedSize(500,200);
}

void Controller::printLog()
{
    for (auto it : log)
    {
        qDebug() << it.col_start << it.row_start << it.col_end << it.row_start;
    }
}

bool Controller::kingCheck(bool isWhite)
{
    Field *figKing;
    if (isWhite)
        figKing = board.getField(wKing);
    else
        figKing = board.getField(bKing);

    if (figKing == nullptr)
        return false;

    for (int i = 1; i <= Board::size; i++)
    {
        for (int j = 1; j <= Board::size; j++)
        {
            Field *from = board.getField(i, j);

            if (from->getFig() != nullptr)
            {
                if (from->getFig()->isWhite() != isWhite)
                {
                    if (from->getFig()->checkMove(from, figKing))
                        return true;
                }
            }
        }
    }
    return false;
}

bool Controller::isStillCheck(Field *king, bool isWhite, Direction dir)
{
    Field *to = king->getNext(dir);

    if (to == nullptr)
        return true;

    if (to->getFig() != nullptr)
    {
        if (to->getFig()->isWhite() == isWhite) //same colour
            return true; //is still check beacuse i cannot move king
    }

    Figure *kick = king->moveFig(to);
    bool ret = kingCheck(isWhite);

    //back changes
    to->moveFig(king);
    to->put(kick);

    return ret;
 }

bool Controller::kingMate(bool isWhite)
{
    //king possible move
    Field *figKing;
    if (isWhite)
        figKing = board.getField(wKing);
    else
        figKing = board.getField(bKing);

    if ((isStillCheck(figKing, isWhite, botDir) && isStillCheck(figKing, isWhite, topDir)
            && isStillCheck(figKing, isWhite, leftDir) && isStillCheck(figKing, isWhite, rightDir)
            && isStillCheck(figKing, isWhite, botLeftDir) && isStillCheck(figKing, isWhite, botRightDir)
            && isStillCheck(figKing, isWhite, topLeftDir) && isStillCheck(figKing, isWhite, topRightDir)) == 0)
        return false;

    return true;
}
