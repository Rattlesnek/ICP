#ifndef CHESSWINDOW_H
#define CHESSWINDOW_H

#include <QDialog>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

#include <vector>

#include "loglist.h"
#include "boardview.h"
#include "controller.h"

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

public:
    int timer; //simulation in miliseconds

public slots:
    void sliderMoved(int);
    void automaticPressed();
    void backPressed();
    void manualPressed();
    void nextPressed();
    void resetPressed();

public:
    explicit ChessWindow(std::vector<LogList> &log, QWidget *parent = nullptr);
    ~ChessWindow();

};

#endif // CHESSWINDOW_H
