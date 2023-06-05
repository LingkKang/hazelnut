#include "defs.h"

#define DELAY 3686400 * 2 // 1 sec or so

/*
Delay the thread for given time which measured in secondes,
not accurate.
Similar to `ksleep_millisec()` in machine mode.
*/
void delay(int time)
{
    uint32 time_in_hz = time * DELAY;
    uint32 start_time = sys_get_hw_time();
    while (sys_get_hw_time() - start_time <= time_in_hz)
        ;
    return;
}
