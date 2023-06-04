#include "defs.h"

#define DELAY 3686400 * 2 // 1 sec or so

void delay(int time)
{
    // TODO();
    uint32 time_in_hz = time * DELAY;
    uint32 finish_time = time_in_hz + sys_get_hw_time();
    while (finish_time <= sys_get_hw_time())
        ;
    return;
}
