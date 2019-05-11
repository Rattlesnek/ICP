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
#include <QMessageBox>

#define FAIL 100 //if regex does not match any string

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
    int stringVersion(QString s);
    void saveChessWindow();


private:
    Ui::MainWindow *ui;

    void insertLongToLog(std::vector<LogList> &log, QString str, bool isPawn, bool isWhite);
    void insertShortToLog(std::vector<LogList> &log, QString str, bool isPawn, bool isWhite);
    void errorMessage(QString error);
};

#endif // MAINWINDOW_H
