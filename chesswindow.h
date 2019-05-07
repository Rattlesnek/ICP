#ifndef CHESSWINDOW_H
#define CHESSWINDOW_H

#include <QDialog>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

#include <vector>

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
    explicit ChessWindow(QWidget *parent = nullptr);
    ~ChessWindow();

};

#endif // CHESSWINDOW_H
