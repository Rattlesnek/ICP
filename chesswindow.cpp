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
    connect(&controller, SIGNAL(signalCheckKing(int)), this, SLOT(writeCheckKing(int)));
    connect(&controller, SIGNAL(signalMoveDelete()), this, SLOT(deleteMove()));
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

    return "D"; //otherwise it is queen
}

QChar ChessWindow::numToCharInd(int a)
{
     return 'a' + (a - 1);
}


/*
 * check == 0 --- not check
 * check == 1 --- check
 * check == 2 --- mate
 */
void ChessWindow::writeMove(Field *from, Field *to, State swap, int check)
{
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

    //print out in long version
    this->ui->log->append(nameFig(from->getFig()->getType()) + numToCharInd(y_start) + QString::number(x_start) +
                          kick + numToCharInd(y_end) + QString::number(x_end) + swapStr + checkStr);
}

void ChessWindow::writeCheckKing(int check)
{
    QString checkStr = "";
    if (check == 1)
        checkStr = "+";
    if (check == 2)
        checkStr = "#";

    this->ui->log->moveCursor(QTextCursor::End);
    this->ui->log->insertPlainText(checkStr);
    this->ui->log->moveCursor(QTextCursor::End);

    if (check == 2)
    {
        QMessageBox messageBox;
        messageBox.critical(nullptr, "", "End game");
        messageBox.setFixedSize(500,200);
    }
}

// https://stackoverflow.com/questions/15326569/removing-last-line-from-qtextedit
void ChessWindow::deleteMove()
{
    this->ui->log->setFocus();
    QTextCursor storeCursorPos = this->ui->log->textCursor();
    this->ui->log->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
    this->ui->log->moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    this->ui->log->moveCursor(QTextCursor::End, QTextCursor::KeepAnchor);
    this->ui->log->textCursor().removeSelectedText();
    this->ui->log->textCursor().deletePreviousChar();
    this->ui->log->setTextCursor(storeCursorPos);
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

