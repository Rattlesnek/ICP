/* Subject:  [ICP] The C++ Programming Language
 *
 * Author: Adam Pankuch (xpanku00.stud.fit.vutbr.cz)
 *         David Miksanik (xmiksa05.stud.fit.vutbr.cz)
 */

#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>

#include <vector>

#include "square.h"


/**
 * @brief The State enum represents different states of FieldView
 */
enum State { wKing, bKing, wQueen, bQueen, wRook, bRook, wBishop, bBishop, wKnight, bKnight, wPawn, bPawn, empty };

/**
 * @brief The FieldView class represents the square together with the possible picture of figure
 */
class FieldView : public QObject
{
    Q_OBJECT

    Square *square; // square in background
    QGraphicsPixmapItem *figurePixmap; // picture of figure

    State state; // state of FieldView
    int row;     // row where its located
    int col;     // col where its located

public:
    /**
     * @brief FieldView constructor
     * @param _row location row
     * @param _col location col
     * @param isWhiteSquare whether it has white or black square
     */
    FieldView(int _row, int _col, bool isWhiteSquare);
    /**
     * @brief FieldView destructor
     */
    ~FieldView();

    /**
     * @brief setPos method sets position of an instance in scene
     * @param x x coordinate
     * @param y y coordinate
     */
    void setPos(double x, double y);
    /**
     * @brief addToScene method adds the instance to scene
     * @param scene graphics scene
     */
    void addToScene(QGraphicsScene *scene);
    /**
     * @brief setState method sets the state of an instance (shows specific figure)
     * @param pixmaps vector of pictures of figures
     * @param _state defines the state
     */
    void setState(std::vector<QPixmap> &pixmaps, State _state);
    /**
     * @brief getState method returns the state of an instance
     * @return
     */
    State getState();
    /**
     * @brief setActive method switches the active / not active state of an instance
     * @param active whether it should be activated
     * @param red whether it should have red color
     */
    void setActive(bool active, bool red);

signals:
    /**
     * @brief signalFieldViewPressed signal emited when mouse clicked on the square
     * @param row location row
     * @param col location col
     * @param active whether the square is active or not
     */
    void signalFieldViewPressed(int row, int col, bool active);

public slots:
    /**
     * @brief slotSquarePressed slot receives the signal from square and emits signalFieldViewPressed
     * @param active
     */
    void slotSquarePressed(bool active);

};

#endif // FIELDVIEW_H
