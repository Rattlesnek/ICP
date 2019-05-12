#ifndef CHESSWINDOW_H
#define CHESSWINDOW_H

#include <QDialog>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QTimer>
#include <QMessageBox>

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

    Ui::ChessWindow *ui; //ui default
    QGraphicsScene *scene; //graphics scene
    QTimer timer; //delay between moves if auto is pressed
    BoardView boardView; //fronted of chesswindow
    Controller controller; //backend of chesswindow

    /**
     * @brief nameFig method return QString representation of State for output
     * @param s State
     * @return QString shortcut of nameFig (define by notation)
     */
    static QString nameFig(State s);
    /**
     * @brief numToCharInd method find a'th char from alphabet
     * @param a int
     * @return QChar a'th char from alphabet (e.g., 2 --> 'b')
     */
    static QChar numToCharInd(int a);

public:
    /**
     * @brief writeMove method write move in long notation
     * @param isWhite true if it is white's move
     * @param start type of figure
     * @param x_start start move from this position
     * @param y_start start move from this position
     * @param x_end end move in this position
     * @param y_end end move in this position
     * @param kick if some figure was kicked
     * @param swap if some figure was swapped
     * @param check if was check (0 - no; 1 - check; 2 - mate)
     */
    void writeMove(int isWhite, State start, int x_start, int y_start, int x_end, int y_end, int kick, State swap, int check);

public slots:
    /**
     * @brief sliderMoved set timer if is changed by user
     */
    void sliderMoved(int);
    /**
     * @brief automaticPressed if auto button is pressed, then send information to controller
     */
    void automaticPressed();
    /**
     * @brief backPressed if back button is pressed, then send information to controller
     */
    void backPressed();
    /**
     * @brief manualPressed if back buttion is pressed, then send information to controller
     */
    void manualPressed();
    /**
     * @brief nextPressed if next buttion is pressed, then send information to controller
     */
    void nextPressed();
    /**
     * @brief resetPressed if reset button is pressed, then send information to controller
     */
    void resetPressed();
    /**
     * @brief automaticMove change automatic moving to manual moving if there are no moves avaible
     */
    void automaticMove();
    /**
     * @brief writeMove method write move in long notation
     * @param from start position
     * @param to end position
     * @param swap if some figure was swapped
     * @param check if was check (0 - no; 1 - check; 2 - mate)
     */
    void writeMove(Field *from, Field *to, State swap, int check);
    /**
     * @brief writeCheckKing append to current move + or # by value in check
     * @param check (0 - no append, 1 - append +; 2 - append #)
     * @param isWhite if true then check white king, else black king
     */
    void writeCheckKing(int check, bool isWhite);
    /**
     * @brief deleteMove
     * @param size
     * @param log
     */
    void deleteMove(int size, std::vector<LogList> log);
    /**
     * @brief markRow highlight given row in log
     * @param row in log
     */
    void markRow(int row);

public:
    /**
     * @brief ChessWindow contructor of chess window (one tab)
     * @param log moves are stored in this vector
     * @param parent always is set nullptr
     */
    explicit ChessWindow(std::vector<LogList> &log, QWidget *parent = nullptr);
    ~ChessWindow();

};

#endif // CHESSWINDOW_H
