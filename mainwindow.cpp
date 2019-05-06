#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    counter{0},
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //remove unused tab
    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);

    //start game
    newChessWindow();
    /*
    chessWindowDialog = new ChessWindow(this);
    chessWindowDialog->show();
    ui->tabWidget->addTab(chessWindowDialog, "chess1");
*/
    connect(ui->new_game, SIGNAL(aboutToShow()), this, SLOT(newChessWindow()));

    connect(ui->delete_game, SIGNAL(aboutToShow()), this, SLOT(deleteChessWindow()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newChessWindow()
{
    counter++;

    QWidget *chessWindowDialog = new ChessWindow(this);
    chessWindowDialog->show();

    ui->tabWidget->addTab(chessWindowDialog, "chess " + QString::number(counter));



    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
}

void MainWindow::deleteChessWindow()
{
    //ui->tabWidget->removeTab()
    qDebug() <<  ui->tabWidget->currentIndex();

    ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
}


