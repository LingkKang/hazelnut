// user activities

#include "types.h"
#include "defs.h"

void task0(void)
{
    kprintf("Task 0 started ...\n");
    int i = 0;
    while (1)
    {
        kprintf("Task 0\t%d\n", i);
        i++;
        // kprintf("Hart id is %d\n", sys_get_hart_id());
        delay(1);
        if (i % 3 == 0)
        {
            task_yield();
        }
        // if (i == 2)
        // {
        //     test_exception();
        // }
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
        delay(1);
        if (i % 5 == 0)
        {
            task_yield();
        }
    }
    return;
}

void task3(void)
{
    while (1)
    {
    }
}

/*
Register all user tasks.
*/
void user_init(void)
{
    task_create(&task0);
    task_create(&task1);
    // task_create(&task3);
}
