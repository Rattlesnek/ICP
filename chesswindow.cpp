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

ChessWindow::ChessWindow(std::vector<LogList> &log, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChessWindow),
    scene{new QGraphicsScene()},
    boardView{scene},
    controller{&boardView, 0, log},
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

    connect(&controller, SIGNAL(signalMoveWrite(Field *, Field *, State)), this, SLOT(writeMove(Field *, Field *, State)));
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

//TODO --- sach+mat
void ChessWindow::writeMove(Field *from, Field *to, State swap)
{
    qDebug() << "here";

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
    //qDebug() << nameFig(to->getFig()->getType()) << numToCharInd(y_start) << x_start << kick << numToCharInd(y_end) << x_end << swapStr;
    this->ui->log->append(nameFig(from->getFig()->getType()) + numToCharInd(y_start) + QString::number(x_start) +
                          kick + numToCharInd(y_end) + QString::number(x_end) + swapStr);
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

