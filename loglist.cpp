/* Subject:  [ICP] The C++ Programming Language
 *
 * Author: Adam Pankuch (xpanku00.stud.fit.vutbr.cz)
 *         David Miksanik (xmiksa05.stud.fit.vutbr.cz)
 */

#include "loglist.h"

LogList::LogList(State _figure, int _row_start, int _col_start,
                int _row_end, int _col_end, State _kick, State _swap, int _check) :
       figure{_figure},
       row_start{_row_start},
       col_start{_col_start},
       row_end{_row_end},
       col_end{_col_end},
       kick{_kick},
       swap{_swap},
       check{_check}
{
}
