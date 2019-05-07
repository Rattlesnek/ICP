#include "boardview.h"

BoardView::BoardView()
{
    preparePixmaps();
}

void BoardView::preparePixmaps()
{
    // vector of pixmaps of figures
    pixmaps = {
        QPixmap(":/images/img/king1.png"),  // white
        QPixmap(":/images/img/king.png"),   // black
        QPixmap(":/images/img/queen1.png"),
        QPixmap(":/images/img/queen.png"),
        QPixmap(":/images/img/rook1.png"),
        QPixmap(":/images/img/rook.png"),
        QPixmap(":/images/img/bishop1.png"),
        QPixmap(":/images/img/bishop.png"),
        QPixmap(":/images/img/horse1.png"),
        QPixmap(":/images/img/horse.png"),
        QPixmap(":/images/img/pawn1.png"),
        QPixmap(":/images/img/pawn.png"),
    };
}

void BoardView::createBoard(QGraphicsScene *scene)
{
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {

            // create a single FieldView (square togheter with pictures of figures)
            FieldView *fw = new FieldView(row+1, col+1, (row + col) % 2 != 0);

            // set atributes of the FieldView
            fw->setPos(50 + col*Square::size, Square::size*7 + 50 - row*Square::size);
            fw->setState(pixmaps, empty);
            fw->addToScene(scene);

            // connect signal from the FieldView to the ChessWindow
            connect(fw, &FieldView::signalFieldViewPressed, this, &BoardView::slotFieldViewPressed);

            // store the FieldView to the vector of FieldViews
            fieldviews.push_back(fw);
        }
    }
}

FieldView *BoardView::getFieldView(int row, int col)
{
    // expects indexes from 1 to 8
    if (row < 1 || row > 8 || col < 1 || col > 8) {
        return nullptr;
    }

    return fieldviews[(row - 1)*8 + (col - 1)];
}

void BoardView::setActiveFieldView(bool active, int row, int col)
{
    FieldView *fw = getFieldView(row, col);
    if (fw == nullptr) {
        return; // TODO Exception
    }

    fw->setActive(active);
}

void BoardView::setStateFieldView(State state, int row, int col)
{
    FieldView *fw = getFieldView(row, col);
    if (fw == nullptr) {
        return; // TODO Exception
    }

    fw->setState(pixmaps, state);
}

void BoardView::setBoardInitialState()
{
    // TODO
    // only example
    int row = 1;
    int col = 2;

    getFieldView(row, col)->setState(pixmaps, bKing);

    getFieldView(2, 5)->setState(pixmaps, wQueen);

    // TODO
}


void BoardView::slotFieldViewPressed(int row, int col, bool active)
{
    qDebug() << "signal from FieldView " << row << " " << col << " " << active;
    emit signalBoardViewPressed(row, col, active);
}
