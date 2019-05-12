/* Subject:  [ICP] The C++ Programming Language
 *
 * Author: Adam Pankuch (xpanku00.stud.fit.vutbr.cz)
 *         David Miksanik (xmiksa05.stud.fit.vutbr.cz)
 */

#ifndef FIELD_H
#define FIELD_H

#include "figure.h"

/**
 * @brief The Direction enum different directions where its possible to move from a Field
 */
enum Direction { topDir, topRightDir, rightDir, botRightDir, botDir, botLeftDir, leftDir, topLeftDir };

/**
 * @brief The Field class represents backend field
 */
class Field
{

public:
    int row; // location row
    int col; // location col
    Figure *figure; // figure on the field or nullptr

    Field *topField; // field to the top from the current field
    Field *botField; // field to the bot from the current field
    Field *rightField; // field to the right from the current field
    Field *leftField; // field to the left from the current field

public:
    /**
     * @brief Field constuctor
     * @param row location row
     * @param col location col
     */
    Field(int row, int col);

    /**
     * @brief getFig method returns a figure on the Field
     * @return a figure or nullptr if ther is none
     */
    Figure *getFig();
    /**
     * @brief isEmpty method checks if the field is empty
     * @return true if field is empty, otherwise false
     */
    bool isEmpty();
    /**
     * @brief put method puts a figure to field if its empty
     * @param fig figure to be put on the field
     * @return true if succesful, false if not
     */
    bool put(Figure *fig);
    /**
     * @brief remove method removes a figure from field
     * @param fig figure to be removed
     * @return true if succesful, false if not
     */
    bool remove(Figure *fig);
    /**
     * @brief moveFig method moves a figure on current field to the specified field
     * @param to field where figure is going to move to
     * @return kicked figure if there was a figure on the "to" field, nullptr otherwise
     */
    Figure *moveFig(Field *to);
    /**
     * @brief getNext method returns a field which is next to current field in given direction
     * @param dir direction
     * @return field next to current field
     */
    Field *getNext(Direction dir);

};

#endif // FIELD_H
