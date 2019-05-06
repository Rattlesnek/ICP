#include "chesswindow.h"
#include "ui_chesswindow.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QDebug>

#include <vector>

#include "square.h"
#include "fieldview.h"

const int SCENE_WIDTH = 600;
const int SCENE_HEIGHT = 600;

ChessWindow::ChessWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChessWindow)
{
    ui->setupUi(this);
    // construct new scene and set its properties
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT);

    // prepare pixmaps of figures - store to vector
    preparePixmaps();

    // create visual board
    createBoard();

    // TODO - example of seting the fields of board
    setBoardInitialState();

    // add scene to view and set properties of view
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(SCENE_WIDTH, SCENE_HEIGHT);
    ui->graphicsView->show();
}

ChessWindow::~ChessWindow()
{
    delete ui;
}

void ChessWindow::createBoard()
{
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {

            // create a single FieldView (square togheter with pictures of figures)
            FieldView *fw = new FieldView(row+1, col+1, (row + col) % 2 == 0);

            // set atributes of the FieldView
            fw->setPos(50 + col*Square::size, Square::size*7 + 50 - row*Square::size);
            fw->setState(pixmaps, empty);
            fw->addToScene(scene);

            // connect signal from the FieldView to the ChessWindow
            connect(fw, &FieldView::signalFieldViewPressed, this, &ChessWindow::slotFieldViewPressed);

            // store the FieldView to the vector of FieldViews
            fieldviews.push_back(fw);
        }
    }
}

void ChessWindow::preparePixmaps()
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

void ChessWindow::setBoardInitialState()
{
    // TODO
    // only example
    int row = 1;
    int col = 3;

    getFieldView(row, col)->setState(pixmaps, bKing);

    getFieldView(2, 4)->setState(pixmaps, wQueen);

    // TODO
}

FieldView *ChessWindow::getFieldView(int row, int col)
{
    // expects indexes from 1 to 8
    if (row < 1 || row > 8 || col < 1 || col > 8) {
        return nullptr;
    }

    return fieldviews[(row - 1)*8 + (col - 1)];
}

void ChessWindow::slotFieldViewPressed(int row, int col, bool active)
{
    qDebug() << "signal from FieldView " << row << " " << col << " " << active;
}
