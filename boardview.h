/* Subject:  [ICP] The C++ Programming Language
 *
 * Author: Adam Pankuch (xpanku00.stud.fit.vutbr.cz)
 *         David Miksanik (xmiksa05.stud.fit.vutbr.cz)
 */

#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QObject>
#include <QPixmap>
#include <QDebug>
#include <QGraphicsScene>

#include <vector>

#include "fieldview.h"

/**
 * @brief The BoardView class represents graphic board
 */
class BoardView : public QObject
{
    Q_OBJECT

    std::vector<QPixmap> pixmaps; // vector of pixmaps of figures
    std::vector<FieldView *> fieldviews; // vector of fieldviews

public:
    /**
     * @brief BoardView constructor of board
     * @param scene graphics scene where it will be added
     */
    BoardView(QGraphicsScene *scene);
    /**
     * @brief preparePixmaps method loads the pictures of figures into vector
     */
    void preparePixmaps();
    /**
     * @brief createBoard method creates the graphic board
     * @param scene graphics scene
     * @param shift_down shift in y axis on scene
     * @param shift_right shif in x axis on scene
     */
    void createBoard(QGraphicsScene *scene, double shift_down, double shift_right);
    /**
     * @brief getFieldView method returs the FieldView instance from given location
     * @param row location row
     * @param col location col
     * @return FieldView instance or nullptr if not found
     */
    FieldView *getFieldView(int row, int col);
    /**
     * @brief setActiveFieldView method activates / deactivates FieldView instance at given location
     * @param active whether should be activated
     * @param red whether should have color red
     * @param row location row
     * @param col location col
     */
    void setActiveFieldView(bool active, bool red, int row, int col);
    /**
     * @brief setStateFieldView method sets FieldView instance at given location to specific state
     * @param state specific state
     * @param row location row
     * @param col location col
     */
    void setStateFieldView(State state, int row, int col);

signals:
    /**
     * @brief signalBoardViewPressed signal emited when mouse clicked on any of the FieldViews
     * @param row location row
     * @param col location col
     * @param active whether it is active or not
     */
    void signalBoardViewPressed(int row, int col, bool active);

public slots:
    /**
     * @brief slotFieldViewPressed slots receives signal from all the FieldViews and emits the signalBoardViewPressed
     * @param row
     * @param col
     * @param active
     */
    void slotFieldViewPressed(int row, int col, bool active);
};

#endif // BOARDVIEW_H
