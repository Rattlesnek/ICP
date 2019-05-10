#include "controller.h"

#include "figure.h"

#include <QDebug>

Controller::Controller(BoardView *_boardView) :
    boardView{_boardView},
    fieldReady{nullptr}
{
    board.setInitialState();

    loadInitialState();
    qDebug() << "load state";
}

void Controller::loadInitialState()
{
    for (auto field : board.board) {
        Figure *fig = field->getFig();
        if (fig == nullptr) {
            continue;
        }

        State stt = fig->getType();
        qDebug() << "figure get" << stt;
        boardView->setStateFieldView(stt, field->row, field->col);
    }
}

void Controller::activatePossibleMoveFields(Figure *fig, Field *from)
{
    for (int i = 1; i < Board::size; i++) {
        for (int j = 1; j < Board::size; j++) {

            if ( fig->checkMove(from, board.getField(i, j)) ) {
                boardView->setActiveFieldView(true, i, j);
            }
        }
    }
}

void Controller::deactivateAllFields()
{
    for (int i = 1; i < Board::size; i++) {
        for (int j = 1; j < Board::size; j++) {
            boardView->setActiveFieldView(false, i, j);
        }
    }
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
            qDebug() << "activate possible fields";
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

            // move picture
            FieldView *toFieldView = boardView->getFieldView(row, col);
            FieldView *fromFieldView = boardView->getFieldView(fieldReady->row, fieldReady->col);
            boardView->moveFigureFieldView(fromFieldView, toFieldView);

            // field moved and now there is none
            fieldReady = nullptr;
        }
        else {
            // player clicked on non active field

        }
    }
}
