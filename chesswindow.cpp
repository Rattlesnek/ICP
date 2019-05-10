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
    scene{new QGraphicsScene()},
    boardView{scene},
    controller{&boardView}
{
    ui->setupUi(this);
    // construct new scene and set its properties
    scene->setSceneRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT);


    connect(&boardView, &BoardView::signalBoardViewPressed, &controller, &Controller::slotBoardViewPressed);

    // add scene to view and set properties of view
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(SCENE_WIDTH, SCENE_HEIGHT);
    ui->graphicsView->show();
}

ChessWindow::~ChessWindow()
{
    delete ui;
}

