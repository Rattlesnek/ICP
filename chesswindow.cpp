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
#include "boardview.h"

const int SCENE_WIDTH = 600;
const int SCENE_HEIGHT = 600;

ChessWindow::ChessWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChessWindow),
    boardView{},
    controller{&boardView}
{
    ui->setupUi(this);
    // construct new scene and set its properties
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT);

    // prepare pixmaps of figures - store to vector
    boardView.preparePixmaps();

    // create visual board
    boardView.createBoard(scene);

    // TODO - example of seting the fields of board
    boardView.setBoardInitialState();

    // add scene to view and set properties of view
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(SCENE_WIDTH, SCENE_HEIGHT);
    ui->graphicsView->show();
}

ChessWindow::~ChessWindow()
{
    delete ui;
}

