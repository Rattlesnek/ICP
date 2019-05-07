#include "field.h"
#include "figure.h"

#include <cmath>

Figure::Figure(bool isWhite) :
    white{isWhite}
{
}

bool Figure::isWhite()
{
    return white;
}


bool King::checkMove(Field *from, Field *to)
{
    if (abs(from->row - to->row) <= 1 && abs(from->col - to->col) <= 1) {
        if (to->get() == nullptr) {
            // to is empty
            return true;
        }
        else if ((this->isWhite() && to->get()->isWhite()) || (! this->isWhite() && ! to->get()->isWhite())) {
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

}

bool Bishop::checkMove(Field *from, Field *to)
{

}

bool Knight::checkMove(Field *from, Field *to)
{

}

bool Rook::checkMove(Field *from, Field *to)
{

}

bool Pawn::checkMove(Field *from, Field *to)
{

}
