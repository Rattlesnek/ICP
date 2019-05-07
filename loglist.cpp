#include "loglist.h"

LogList::LogList(State _figure, int _x_start, int _y_start,
                int _x_end, int _y_end, State _kick) :
       figure{_figure},
       x_start{_x_start},
       y_start{_y_start},
       x_end{_x_end},
       y_end{_y_end},
       kick{_kick}
{
}
