#ifndef CHESSWINDOW_H
#define CHESSWINDOW_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

namespace Ui {
class ChessWindow;
}

class ChessWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChessWindow(QWidget *parent = nullptr);
    ~ChessWindow();

private:
    Ui::ChessWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
};

#endif // CHESSWINDOW_H
