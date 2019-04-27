#include "chesswindow.h"
#include "ui_chesswindow.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

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
    QGraphicsRectItem *rect = new QGraphicsRectItem();
    rect->setRect(20, 20, 100, 100);
    scene->addItem(rect);


    // construct new view
    view = new QGraphicsView(scene);
    view->setFixedSize(SCENE_WIDTH, SCENE_HEIGHT);
    scene->setSceneRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    view->show();
    // add view to the grid of dialog window
    ui->gameLayout->addWidget(view);
}

ChessWindow::~ChessWindow()
{
    delete ui;
}
