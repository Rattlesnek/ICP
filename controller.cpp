#include "controller.h"

Controller::Controller(BoardView *_boardView) :
    boardView{_boardView}
{

}

void Controller::slotFieldViewPressed(int row, int col, bool active)
{
//    if (board.getField(row, col)->get() != nullptr) {
//        boardView->setActiveFieldView(! active, row, col);
//    }
}
