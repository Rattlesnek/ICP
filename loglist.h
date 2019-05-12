/* Subject:  [ICP] The C++ Programming Language
 *
 * Author: Adam Pankuch (xpanku00.stud.fit.vutbr.cz)
 *         David Miksanik (xmiksa05.stud.fit.vutbr.cz)
 */

#ifndef LOGLIST_H
#define LOGLIST_H

#include "fieldview.h"

class LogList
{
public:
    /**
     * @brief LogList contructor
     * @param _figure
     * @param _row_start
     * @param _col_start
     * @param _row_end
     * @param _col_end
     * @param _kick
     * @param _swap
     * @param check
     */
    LogList(State _figure, int _row_start, int _col_start,
                    int _row_end, int _col_end, State _kick, State _swap, int check = 0);

    State figure; //type of figure
    int row_start; //x start coordinate
    int col_start; //y start coordinate
    int row_end; //x end coordinate
    int col_end; //y end cordinate
    State kick; //what figure was kicked
    State swap; //new swapped figure
    int check; //if king is check(mate) --- 0 - no; 1 - check; 2 - mate
};

#endif // LOGLIST_H
