#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chesswindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void newChessWindow();

private:
    Ui::MainWindow *ui;
    ChessWindow *chessWindowDialog;

};

#endif // MAINWINDOW_H
