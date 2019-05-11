#include "field.h"
#include "figure.h"

#include <QDebug>

#include <cmath>

Figure::Figure(bool isWhite) :
    white{isWhite}
{
}

Figure::~Figure()
{
}

bool Figure::isWhite()
{
    return white;
}


bool King::checkMove(Field *from, Field *to)
{
    if (abs(from->row - to->row) <= 1 && abs(from->col - to->col) <= 1) {
        if (to->getFig() == nullptr) {
            // to is empty
            return true;
        }
        else if ((this->isWhite() && to->getFig()->isWhite()) || (! this->isWhite() && ! to->getFig()->isWhite())) {
            return false;
        }
        else {
            return true;
        }
    }
    return false;
}


bool Queen::checkMove(Field *from, Field *to)
{
    //qDebug() << "QUEEN: checkMove()";

    return checkMoveBishop(from, to) || checkMoveRook(from, to);
}

bool Bishop::checkMove(Field *from, Field *to)
{
    //qDebug() << "BISHOP: checkMove()";

    return checkMoveBishop(from, to);
}

bool Rook::checkMove(Field *from, Field *to)
{
    //qDebug() << "ROOK: checkMove()";

    return checkMoveRook(from, to);
}

bool Knight::checkMove(Field *from, Field *to)
{
    //qDebug() << "KNIGHT: checkMove()";

    //if to end figure is no null, then must be opposite colour
    if (to->getFig() != nullptr)
    {
        if ((this->isWhite() && to->getFig()->isWhite()) || (!this->isWhite() && !to->getFig()->isWhite()))
            return false;
    }

    //start coordinates
    int x_start = from->col;
    int y_start = from->row;

    //end coordiates
    int x_end = to->col;
    int y_end = to->row;

    int x_diff = x_start - x_end;
    int y_diff = y_start - y_end;

    return ((abs(x_diff) == 2 && abs(y_diff) == 1) || (abs(x_diff) == 1 && abs(y_diff) == 2));
}


bool Pawn::checkMove(Field *from, Field *to)
{
    //qDebug() << "Pawn: checkMove()";

    //if to end figure is no null, then must be opposite colour
    if (to->getFig() != nullptr)
    {
        if ((this->isWhite() && to->getFig()->isWhite()) || (!this->isWhite() && !to->getFig()->isWhite()))
            return false;
    }

    bool isWhite = from->getFig()->isWhite();

    //start coordinates
    int x_start = from->col;
    int y_start = from->row;

    //end coordiates
    int x_end = to->col;
    int y_end = to->row;

    int x_diff = x_start - x_end;
    int y_diff = y_start - y_end;

    Field *temp = from;

    //consider a special starting moves
    if (y_start == 2 && isWhite && (y_start + 2) == y_end && x_diff == 0)
    {
        temp = temp->getNext(topDir);
        if (temp->getFig() == nullptr)
            return true;
        else
            return false;
    }
    else if (y_start == 7 && !isWhite && (y_start - 2) == y_end && x_diff == 0)
    {
         temp = temp->getNext(botDir);
         if (temp->getFig() == nullptr)
            return true;
         else
             return false;
    }

    //in others case we move only by one spep
    if (abs(y_diff) != 1)
        return false;

    //move forward (not kick)
    if (x_diff == 0)
    {
        if (isWhite && y_diff == -1) //white pawn
        {
            temp = temp->getNext(topDir);
            if (temp->getFig() == nullptr)
                return true;
            else
                return false;

        }
        else if (!isWhite && y_diff == 1) //black pawn
        {
            temp = temp->getNext(botDir);
            if (temp->getFig() == nullptr)
                return true;
            else
                return false;
        }
    }
    else if (x_diff == 1) //possible kick someone in the left
    {
        if (isWhite && y_diff == -1) //white pawn
        {
            temp = temp->getNext(topLeftDir);
            if (temp->getFig() == nullptr)
                return false;
            else
                return true;
        }
        else if (!isWhite && y_diff == 1) //black pawn
        {
            temp = temp->getNext(botLeftDir);
            if (temp->getFig() == nullptr)
                return false;
            else
                return true;
        }
    }
    else if (x_diff == -1) //possible kick someone in the right
    {
        if (isWhite && y_diff == -1) //white pawn
        {
            temp = temp->getNext(topRightDir);
            if (temp->getFig() == nullptr)
                return false;
            else
                return true;
        }
        else if (!isWhite && y_diff == 1) //black pawn
        {
            temp = temp->getNext(botRightDir);
            if (temp->getFig() == nullptr)
                return false;
            else
                return true;
        }
    }
    return false;
}

bool Figure::checkMoveBishop(Field *from, Field *to)
{
    //if to end figure is no null, then must be opposite colour
    if (to->getFig() != nullptr)
    {
        if ((this->isWhite() && to->getFig()->isWhite()) || (!this->isWhite() && !to->getFig()->isWhite()))
            return false;
    }

    //start coordinates
    int x_start = from->col;
    int y_start = from->row;

    //end coordiates
    int x_end = to->col;
    int y_end = to->row;

    int x_diff = x_start - x_end;
    int y_diff = y_start - y_end;

    if (abs(x_diff) != abs(y_diff))
        return false;

    Field *temp = from;
    if (y_diff < 0 && x_diff < 0)
    {
        for (int i = y_start; i < y_end-1; i++) //-1 do not check the last field, beacuse is
                                                    //check already in the beginning of the function
        {
            temp = temp->getNext(topRightDir);
            if (temp->getFig() != nullptr)
                return false;
        }
    }
    else if (y_diff < 0 && x_diff > 0)
    {
        for (int i = y_start; i < y_end-1; i++) //similary ^^^
        {
            temp = temp->getNext(topLeftDir);
            if (temp->getFig() != nullptr)
                return false;
         }
      }
    else if (y_diff > 0 && x_diff < 0)
    {
        for (int i = y_start; i > y_end+1; i--) //similary ^^^
        {
            temp = temp->getNext(botRightDir);
            if (temp->getFig() != nullptr)
                return false;
        }
    }
    else
    {
        for (int i = y_start; i > y_end+1; i--) //similary ^^^
        {
            temp = temp->getNext(botLeftDir);
            if (temp->getFig() != nullptr)
                return false;
        }
    }

    return true; //everything OK
}

bool Figure::checkMoveRook(Field *from, Field *to)
{
    //start coordinates
    int x_start = from->col;
    int y_start = from->row;

    //end coordiates
    int x_end = to->col;
    int y_end = to->row;

    //if to end figure is no null, then must be opposite colour
    if (to->getFig() != nullptr)
    {
        if ((this->isWhite() && to->getFig()->isWhite()) || (!this->isWhite() && !to->getFig()->isWhite()))
            return false;
    }

    Field *temp = from;
    //in same collumn
    if (abs(x_start - x_end) == 0 )
    {
        int y_diff = y_start - y_end;

        if (y_diff < 0)
        {
            for (int i = y_start; i < y_end-1; i++) //-1 do not check the last field, beacuse is
                                                    //check already in the beginning of the function
            {
                temp = temp->getNext(topDir);
                if (temp->getFig() != nullptr)
                    return false;
            }
        }
        else
        {
            for (int i = y_start; i > y_end+1; i--) //similary ^^^
            {
                temp = temp->getNext(botDir);
                if (temp->getFig() != nullptr)
                    return false;
            }
        }
    //in same row
    }
    else if (abs(y_start - y_end) == 0)
    {
        int x_diff = x_start - x_end;

        if (x_diff > 0)
        {
            for (int i = x_start; i > x_end+1; i--) //similary ^^^
            {
                temp = temp->getNext(leftDir);
                if (temp->getFig() != nullptr)
                    return false;
            }
        }
        else
        {
            for (int i = x_start; i < x_end-1; i++) //similary ^^^
            {
                temp = temp->getNext(rightDir);
                if (temp->getFig() != nullptr)
                    return false;
            }
        }
    }
    //not in same row or column --> false
    else
    {
        return false;
    }

    return true; //everything OK
}
