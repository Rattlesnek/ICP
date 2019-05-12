/* Subject:  [ICP] The C++ Programming Language
 *
 * Author: Adam Pankuch (xpanku00.stud.fit.vutbr.cz)
 *         David Miksanik (xmiksa05.stud.fit.vutbr.cz)
 */

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

    int counter; //number of created chess window

public:
    /**
     * @brief MainWindow contructor
     * @param parent
     */
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    /**
     * @brief newChessWindow create new chess window
     */
    void newChessWindow();
    /**
     * @brief deleteChessWindow delete current  chess window
     */
    void deleteChessWindow();
    /**
     * @brief loadChessWindow create new window in which are store moves from file
     */
    void loadChessWindow();
    /**
     * @brief stringVersion return type of string (0 - pawn, long version; 1 - no pawn, long version
     *                                             2 - pawn, shor version; 3 - no pawn short version)
     * @param s move
     * @return type of string
     */
    int stringVersion(QString s);
    //void saveChessWindow();

private:
    Ui::MainWindow *ui;
    /**
     * @brief insertLongToLog slot receives signal if is needed store move from file to log
     *          and the string is in the LONG version
     * @param log store moves
     * @param str input string from file
     * @param isPawn pawn plays
     * @param isWhite true if white move else black move
     */
    void insertLongToLog(std::vector<LogList> &log, QString str, bool isPawn, bool isWhite);
    /**
     * @brief insertShortToLog slot receives signal if is needed store move from file to log
     *          and the string is in the SHORT version
     * @param log store moves
     * @param str input string from file
     * @param isPawn pawn plays
     * @param isWhite true if white move else black move

     */
    void insertShortToLog(std::vector<LogList> &log, QString str, bool isPawn, bool isWhite);
    /**
     * @brief errorMessage slot receives signal if some error occured
     * @param error message of error (this text will be display)
     */
    void errorMessage(QString error);
};

#endif // MAINWINDOW_H
