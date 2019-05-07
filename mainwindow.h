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

    int counter;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void newChessWindow();
    void deleteChessWindow();
    void loadChessWindow();
    void saveChessWindow();


private:
    Ui::MainWindow *ui;

    void getFigure(QString str);
    void getStartX(QString str);
};

#endif // MAINWINDOW_H
