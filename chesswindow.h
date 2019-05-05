#ifndef CHESSWINDOW_H
#define CHESSWINDOW_H

#include <QDialog>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

#include <vector>

#include "fieldview.h"
#include "board.h"

namespace Ui {
class ChessWindow;
}

class ChessWindow : public QDialog
{
    Q_OBJECT

    Ui::ChessWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    Board board;

    std::vector<QPixmap> pixmaps; // vector of pixmaps of figures
    std::vector<FieldView *> fieldviews; // vector of fields

public:
    explicit ChessWindow(QWidget *parent = nullptr);
    ~ChessWindow();

    void createBoard();
    void preparePixmaps();
    void setBoardInitialState();
    FieldView *getFieldView(int row, int col);

public slots:
    void slotFieldViewPressed(int row, int col, bool active);

};

#endif // CHESSWINDOW_H
