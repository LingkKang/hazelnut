
#include "types.h"
#include "defs.h"

#define DELAY 3686400 * 2 // 1 sec or so

void task0(void)
{
    kprintf("Task 0 started ...\n");
    int i = 0;
    while (1)
    {
        kprintf("Task 0\t%d\n", i);
        i++;
        ksleep_millisec(DELAY);
        if (i % 3 == 0) {
            task_pause();
        }
    }
    return;
}

void task1(void)
{
    kprintf("Task 1 started ...\n");
    int i = 0;
    while (1)
    {
        kprintf("Task 1\t%d\n", i);
        i++;
        ksleep_millisec(DELAY);
        if (i % 5 == 0) {
            task_pause();
        }
    }
    return;
}

void user_init(void){
    task_create(&task0);
    task_create(&task1);
}
