#ifndef LOGLIST_H
#define LOGLIST_H

#include "fieldview.h"

class LogList
{
public:
    LogList(State _figure, int _x_start, int _y_start,
                    int _x_end, int _y_end, State _kick, State _swap);

    State figure; //type of figure
    int x_start; //x start coordinate
    int y_start; //y start coordinate
    int x_end; //x end coordinate
    int y_end; //y end cordinate
    State kick; //what figure was kicked
    State swap; //new swapped figure
};

#endif // LOGLIST_H
