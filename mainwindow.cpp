#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->play, SIGNAL(released()), this, SLOT(newChessWindow()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newChessWindow()
{
    qDebug() << "play";
    chessWindowDialog = new ChessWindow(this);
    chessWindowDialog->show();
}
