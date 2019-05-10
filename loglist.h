#ifndef LOGLIST_H
#define LOGLIST_H

#include "fieldview.h"

class LogList
{
public:
    LogList(State _figure, int _row_start, int _col_start,
                    int _row_end, int _col_end, State _kick, State _swap);

    State figure; //type of figure
    int row_start; //x start coordinate
    int col_start; //y start coordinate
    int row_end; //x end coordinate
    int col_end; //y end cordinate
    State kick; //what figure was kicked
    State swap; //new swapped figure
};

#endif // LOGLIST_H
