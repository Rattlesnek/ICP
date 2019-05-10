#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chesswindow.h"
#include "loglist.h"
#include "field.h"
#include "board.h"
#include "ui_mainwindow.h"
#include "chesswindow.h"
#include <QMainWindow>
#include <QDebug>
#include <QInputDialog>
#include <QFileInfo>
#include <QFile>
#include <QStringRef>
#include <QRegExp>
#include <vector>
#include <QTextEdit>
#include <QTextEdit>

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

    void insertToLog(ChessWindow *chess, QString str, bool isPawn, bool isWhite);
};

#endif // MAINWINDOW_H
