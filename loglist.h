#ifndef LOGLIST_H
#define LOGLIST_H

#include "fieldview.h"

class LogList
{
public:
    LogList(State _figure, int _x_start, int _y_start,
                    int _x_end, int _y_end, State _kick);

    State figure;
    int x_start;
    int y_start;
    int x_end;
    int y_end;
    State kick;
};

#endif // LOGLIST_H
