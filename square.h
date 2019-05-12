/* Subject:  [ICP] The C++ Programming Language
 *
 * Author: Adam Pankuch (xpanku00.stud.fit.vutbr.cz)
 *         David Miksanik (xmiksa05.stud.fit.vutbr.cz)
 */

#ifndef SQUARE_H
#define SQUARE_H


#include <QObject>
#include <QColor>
#include <QBrush>
#include <QGraphicsRectItem>

/**
 * @brief The Square class represents the graphic square
 */
class Square : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

    QBrush brush; // brush for the color of square
    bool white;   // true if the square is white
    bool active;  // true if the square is active (a figure is ready to move there)

public:
    static double size; // size of square


private:
    /**
     * @brief setColor method sets color of square
     * @param color
     */
    void setColor(QColor color);

public:
    /**
     * @brief Square constructor
     * @param isWhite whether the square is white or black
     */
    Square(bool isWhite);

    /**
     * @brief setOriginalColor method sets square to either white or black color
     * @param isWhite whether the square should be white or black
     */
    void setOriginalColor(bool isWhite);

    /**
     * @brief setActive method changes the color of square according to isActive
     * @param isActive whether the square should be activated
     * @param red whether the square should be red
     */
    void setActive(bool isActive, bool red);

    /**
     * @brief isActive method returns true of square is active
     * @return true if square is active, false otherwise
     */
    bool isActive();

    /**
     * @brief mousePressEvent event when mouse clicked on square
     * @param event
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    /**
     * @brief signalSquarePressed signal emited when mouse clicked on square
     * @param active whether the square is active
     */
    void signalSquarePressed(bool active);

};


#endif // SQUARE_H
