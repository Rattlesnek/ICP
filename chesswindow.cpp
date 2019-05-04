#include "chesswindow.h"
#include "ui_chesswindow.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QDebug>

#include "fieldview.h"

const int SCENE_WIDTH = 400;
const int SCENE_HEIGHT = 400;

ChessWindow::ChessWindow(QWidget *parent) :
    QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
    ui(new Ui::ChessWindow)
{
    ui->setupUi(this);
    // construct new scene
    scene = new QGraphicsScene();


    // example
//    Field *rect = new Field();
    //rect->setRect(20, 20, 100, 100);
//    rect->setColor(QColor("black"));

    QGraphicsPixmapItem *item = new QGraphicsPixmapItem();
    item->setPixmap(QPixmap(":/images/img/pawn1.png"));
    //rect->setPos(20, 20);
    scene->addItem(item);
    item->show();
    item->setPos(100, 100);

    FieldView *rect = new FieldView();
    rect->setRect(0,0,100,100);
    rect->setPos(200,200);
    rect->show();
    scene->addItem(rect);


    connect(rect, &FieldView::signalFieldPressed, this, &ChessWindow::slotFieldPressed);


    // construct new view
    ui->graphicsView->setFixedSize(SCENE_WIDTH, SCENE_HEIGHT);
    scene->setSceneRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    ui->graphicsView->show();
}

ChessWindow::~ChessWindow()
{
    delete ui;
}


void ChessWindow::slotFieldPressed(int x, int y)
{
    qDebug() << "signal received " << x << y;
}
