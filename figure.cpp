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
    return false;
}

bool Bishop::checkMove(Field *from, Field *to)
{
    return false;
}

bool Knight::checkMove(Field *from, Field *to)
{
    return false;
}

bool Rook::checkMove(Field *from, Field *to)
{
    return false;
}

bool Pawn::checkMove(Field *from, Field *to)
{
    return false;
}


