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
    controller{&boardView, 0},
    timer{2500}
{
    ui->setupUi(this);
    // construct new scene and set its properties
    scene->setSceneRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT);


    connect(&boardView, &BoardView::signalBoardViewPressed, &controller, &Controller::slotBoardViewPressed);

    // add scene to view and set properties of view
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(SCENE_WIDTH, SCENE_HEIGHT);
    ui->graphicsView->show();

    //get value of slider
    connect(ui->timer, SIGNAL(valueChanged(int)), this, SLOT(sliderMoved(int)));

    connect(ui->automatic, SIGNAL(released()), this, SLOT(automaticPressed()));
    connect(ui->back, SIGNAL(released()), this, SLOT(backPressed()));
    connect(ui->manual, SIGNAL(released()), this, SLOT(manualPressed()));
    connect(ui->next, SIGNAL(released()), this, SLOT(nextPressed()));
    connect(ui->reset, SIGNAL(released()), this, SLOT(resetPressed()));
}

void ChessWindow::sliderMoved(int value)
{
    timer = value * 50;
}

void ChessWindow::automaticPressed()
{
    qDebug() << "automaticPressed()";
}

void ChessWindow::backPressed()
{
    qDebug() << "backPressed()";
    controller.back();
}

void ChessWindow::manualPressed()
{
    qDebug() << "manualPressed()";
}

void ChessWindow::nextPressed()
{
    qDebug() << "nextPressed()";
    controller.next();
}

void ChessWindow::resetPressed()
{
    qDebug() << "resetPressed()";
}

ChessWindow::~ChessWindow()
{
    delete ui;
}

