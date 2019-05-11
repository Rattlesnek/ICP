#ifndef CHESSWINDOW_H
#define CHESSWINDOW_H

#include <QDialog>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

#include <vector>
#include <string>

#include "loglist.h"
#include "boardview.h"
#include "controller.h"
#include "field.h"

namespace Ui {
class ChessWindow;
}

class ChessWindow : public QWidget
{
    Q_OBJECT

    Ui::ChessWindow *ui;
    QGraphicsScene *scene;

    BoardView boardView;
    Controller controller;

    static QString nameFig(State s);
    static QChar numToCharInd(int a);

public:
    int timer; //simulation in miliseconds
 //   static void writeMove(Field *from, Field *to, State swap);

public slots:
    void sliderMoved(int);
    void automaticPressed();
    void backPressed();
    void manualPressed();
    void nextPressed();
    void resetPressed();
    void writeMove(Field *from, Field *to, State swap);
    void deleteMove();

public:
    explicit ChessWindow(std::vector<LogList> &log, QWidget *parent = nullptr);
    ~ChessWindow();

};

#endif // CHESSWINDOW_H
