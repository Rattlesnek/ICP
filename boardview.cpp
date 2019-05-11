#include "boardview.h"

#include <QFont>
#include <QGraphicsSimpleTextItem>

BoardView::BoardView(QGraphicsScene *scene)
{
    preparePixmaps();
    createBoard(scene, Square::size, 0);
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

void BoardView::createBoard(QGraphicsScene *scene, double shift_down, double shift_right)
{       
    double textShift_down = 11.5;
    double textShift_right = 22.5;

    QFont font;
    font.setPixelSize(30);

    for (int row = 0; row < 8; row++) {
        QGraphicsSimpleTextItem *text = new QGraphicsSimpleTextItem();
        text->setText(QString::number(row + 1));
        text->setFont(font);
        text->setPos(shift_right + textShift_right, shift_down + textShift_down + Square::size*7 - row*Square::size);
        text->show();
        scene->addItem(text);

        for (int col = 0; col < 8; col++) {

            // create a single FieldView (square togheter with pictures of figures)
            FieldView *fw = new FieldView(row+1, col+1, (row + col) % 2 != 0);

            // set atributes of the FieldView
            fw->setPos(shift_right + (col + 1)*Square::size, shift_down + Square::size*7 - row*Square::size);
            fw->setState(pixmaps, empty);
            fw->addToScene(scene);

            // connect signal from the FieldView to the ChessWindow
            connect(fw, &FieldView::signalFieldViewPressed, this, &BoardView::slotFieldViewPressed);

            // store the FieldView to the vector of FieldViews
            fieldviews.push_back(fw);
        }
    }

    for (int col = 0; col < 8; col++) {
        QGraphicsSimpleTextItem *text = new QGraphicsSimpleTextItem();
        char c = static_cast<char>(65 + col);
        text->setText(QString(c));
        text->setFont(font);
        text->setPos(shift_right + textShift_right + (col + 1)*Square::size, shift_down + textShift_down + Square::size*8);
        text->show();
        scene->addItem(text);
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
        qDebug() << "Field view not found: row " << row << " col " << col;
        return; // TODO Exception
    }

    fw->setActive(active);
}

void BoardView::setStateFieldView(State state, int row, int col)
{
    FieldView *fw = getFieldView(row, col);
    if (fw == nullptr) {
        qDebug() << "Field view not found: row " << row << " col " << col;
        return; // TODO Exception
    }
    fw->setState(pixmaps, state);
}


void BoardView::slotFieldViewPressed(int row, int col, bool active)
{
    emit signalBoardViewPressed(row, col, active);
}
