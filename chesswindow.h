#ifndef CHESSWINDOW_H
#define CHESSWINDOW_H

#include <QDialog>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QTimer>

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

    QTimer timer;

    BoardView boardView;
    Controller controller;

    static QString nameFig(State s);
    static QChar numToCharInd(int a);

 //   static void writeMove(Field *from, Field *to, State swap);

public slots:
    void sliderMoved(int);
    void automaticPressed();
    void backPressed();
    void manualPressed();
    void nextPressed();
    void resetPressed();
    void automaticMove();
    void writeMove(Field *from, Field *to, State swap);
    void deleteMove();

public:
    explicit ChessWindow(std::vector<LogList> &log, QWidget *parent = nullptr);
    ~ChessWindow();

};

#endif // CHESSWINDOW_H
