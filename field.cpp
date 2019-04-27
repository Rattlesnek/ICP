#include "field.h"

Field::Field() :
    figure{nullptr}
{
}

Figure *Field::get()
{
    return figure;
}

bool Field::isEmpty()
{
    return figure == nullptr;
}

bool Field::put(Figure *fig)
{
    if (isEmpty()) {
        figure = fig;
        return true;
    }
    else {
        return false;
    }
}

bool Field::remove(Figure *fig)
{
    if (figure == fig) {
        figure = nullptr;
        return true;
    }
    else {
        return false;
    }
}


