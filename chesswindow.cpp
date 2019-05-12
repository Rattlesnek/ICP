/* Subject:  [ICP] The C++ Programming Language
 *
 * Author: Adam Pankuch (xpanku00.stud.fit.vutbr.cz)
 *         David Miksanik (xmiksa05.stud.fit.vutbr.cz)
 */

#include "chesswindow.h"
#include "ui_chesswindow.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QTableWidget>
#include <QTableWidgetItem>

#include <vector>

#include "square.h"
#include "boardview.h"

const int SCENE_WIDTH = static_cast<int>(10 * Square::size);
const int SCENE_HEIGHT = static_cast<int>(10 * Square::size);

ChessWindow::ChessWindow(std::vector<LogList> &log, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChessWindow),
    scene{new QGraphicsScene()},
    boardView{scene},
    controller{&boardView, 0, log}
{
    ui->setupUi(this);
    // construct new scene and set its properties
    scene->setSceneRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT);


    connect(&boardView, &BoardView::signalBoardViewPressed, &controller, &Controller::slotBoardViewPressed);

    // add scene to view and set properties of view
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(SCENE_WIDTH, SCENE_HEIGHT);
    ui->graphicsView->show();
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    ui->log2->setColumnWidth(0, 90);
    ui->log2->setColumnWidth(1, 90);
    //mark all row if is clicked only on columnv
    ui->log2->setSelectionBehavior(QAbstractItemView::SelectRows);
    bool player = true;
    for (auto it : log)
    {
        writeMove(player, it.figure, it.row_start, it.col_start, it.row_end, it.col_end, it.kick, it.swap, it.kick);
        player = player ? false : true;
    }

    //get value of slider
    connect(ui->timer, SIGNAL(valueChanged(int)), this, SLOT(sliderMoved(int)));

    connect(ui->automatic, SIGNAL(released()), this, SLOT(automaticPressed()));
    connect(ui->back, SIGNAL(released()), this, SLOT(backPressed()));
    connect(ui->manual, SIGNAL(released()), this, SLOT(manualPressed()));
    connect(ui->next, SIGNAL(released()), this, SLOT(nextPressed()));
    connect(ui->reset, SIGNAL(released()), this, SLOT(resetPressed()));

    connect(&timer, SIGNAL(timeout()), this, SLOT(automaticMove()));
    // set interval to 1 sec
    timer.setInterval(1000);

    connect(&controller, SIGNAL(signalMoveWrite(Field *, Field *, State, int)), this, SLOT(writeMove(Field *, Field *, State, int)));
    connect(&controller, SIGNAL(signalCheckKing(int, bool)), this, SLOT(writeCheckKing(int, bool)));
    connect(&controller, SIGNAL(signalMoveDelete(int, std::vector<LogList>)), this, SLOT(deleteMove(int, std::vector<LogList>)));

    connect(&controller, SIGNAL(signalMarkRow(int)), this, SLOT(markRow(int)));
}

QString ChessWindow::nameFig(State s)
{
    if (s == wPawn || s == bPawn)
        return "";
    if (s == wRook || s == bRook)
        return "V";
    if (s == wBishop || s == bBishop)
        return "S";
    if (s == wKnight || s == bKnight)
        return "J";
    if (s == wKing || s == bKing)
        return "K";
    if (s == wQueen || s == bQueen)
        return "D";

    return "";
}

QChar ChessWindow::numToCharInd(int a)
{
     return 'a' + (a - 1);
}

void ChessWindow::writeMove(int isWhite, State start, int x_start, int y_start, int x_end, int y_end, int kick, State swap, int check)
{
    QString figName = nameFig(start);
    QString kickStr = "";
    if (kick != empty)
        kickStr = "x";
    QString swapStr = nameFig(swap);

    QString strCheck = "";
    if (check == 1)
        strCheck = "+";
    else if (check == 2)
        strCheck = "-";

    qDebug() << x_start << y_start << x_end << y_end ;


    QString strOut;
    if (x_start != 0 && y_start != 0) {
        // long notation
        strOut = figName + numToCharInd(y_start) + QString::number(x_start) +
            kickStr + numToCharInd(y_end) + QString::number(x_end) + swapStr + strCheck;
    }
    else {
        // short notation
        strOut = figName + kickStr + numToCharInd(y_end) + QString::number(x_end) + swapStr + strCheck;
    }

    int row = ui->log2->rowCount();
    if (isWhite)
    {
        this->ui->log2->setRowCount(row + 1);
        this->ui->log2->setItem(row, 0, new QTableWidgetItem(strOut));
    }
    else
    {
        this->ui->log2->setItem(row-1, 1, new QTableWidgetItem(strOut));
    }
}

void ChessWindow::markRow(int row)
{
    ui->log2->selectRow(row);
}


/*
 * check == 0 --- not check
 * check == 1 --- check
 * check == 2 --- mate
 */
void ChessWindow::writeMove(Field *from, Field *to, State swap, int check)
{
    bool isWhite = from->getFig()->isWhite();

    QString checkStr = "";
    if (check == 1)
        checkStr = "+";
    if (check == 2)
        checkStr = "#";

    //get coordinates
    int x_start = from->row;
    int y_start = from->col;
    int x_end = to->row;
    int y_end = to->col;

    QString kick = "";
    if (to->getFig() != nullptr) //we must kick
        kick = "x";

    QString swapStr = "";
    if (swap != empty)
    {
        swapStr = nameFig(swap);
    }

    //output string
    QString strOut = nameFig(from->getFig()->getType()) + numToCharInd(y_start) + QString::number(x_start) +
            kick + numToCharInd(y_end) + QString::number(x_end) + swapStr + checkStr;

    //print out in long version
    int row = ui->log2->rowCount();
    if (isWhite)
    {
        this->ui->log2->setRowCount(row + 1);
        this->ui->log2->setItem(row, 0, new QTableWidgetItem(strOut));
        this->ui->log2->selectRow(row);
    }
    else
    {
        this->ui->log2->setItem(row-1, 1, new QTableWidgetItem(strOut));
    }
    //-------------------
    qDebug() << "WRITEEEEEEEEEEEEE";


    //print out in long version
    //this->ui->log->append(nameFig(from->getFig()->getType()) + numToCharInd(y_start) + QString::number(x_start) +
    //                      kick + numToCharInd(y_end) + QString::number(x_end) + swapStr + checkStr);
}

void ChessWindow::writeCheckKing(int check, bool isWhite)
{
    QString checkStr = "";
    if (check == 1)
        checkStr = "+";
    if (check == 2)
        checkStr = "#";

//    this->ui->log->moveCursor(QTextCursor::End);
//    this->ui->log->insertPlainText(checkStr);
//    this->ui->log->moveCursor(QTextCursor::End);

    //print out in long version
    int row = ui->log2->rowCount();
    if (isWhite)
    {
        this->ui->log2->item(row-1, 0)->setText( this->ui->log2->item(row-1, 0)->text() + checkStr );
    }
    else
        this->ui->log2->item(row-1, 1)->setText( this->ui->log2->item(row-1, 1)->text() + checkStr );
    //----------------------

    if (check == 2)
    {
        QMessageBox messageBox;
        messageBox.critical(nullptr, "", "End game");
        messageBox.setFixedSize(500,200);
    }
}


void ChessWindow::deleteMove(int size, std::vector<LogList> log)
{    
    int row = this->ui->log2->rowCount()-1;

    if (size == 0 || row == -1)
        return ;

    // delete all
    ui->log2->setRowCount(0);

    // load all
    bool player = true;
    for (auto it : log)
    {
        writeMove(player, it.figure, it.row_start, it.col_start, it.row_end, it.col_end, it.kick, it.swap, it.kick);
        player = ! player; // switch whose turn it is
    }
}

void ChessWindow::sliderMoved(int value)
{
    qDebug() << "interval set to: " << value *20;
    timer.setInterval(value * 20);
}

void ChessWindow::automaticPressed()
{
    qDebug() << "automaticPressed()";
    timer.start();
}

void ChessWindow::backPressed()
{
    qDebug() << "backPressed()";
    controller.back();
}

void ChessWindow::manualPressed()
{
    qDebug() << "manualPressed()";
    timer.stop();
}

void ChessWindow::nextPressed()
{
    qDebug() << "nextPressed()";
    controller.next();
}

void ChessWindow::resetPressed()
{
    qDebug() << "resetPressed()";
    controller.reset();
    this->ui->log2->setRowCount(0);
}

void ChessWindow::automaticMove()
{
    qDebug() << "automaticMove()";
    if (controller.next() == false) {
        // in case there are no next moves to execute
        // switch to manual
        manualPressed();
    }
}

ChessWindow::~ChessWindow()
{
    delete ui;
}

