// enter to hazelnut kernel

#include "defs.h"

void enter(void)
{
    uart_init();
    uart_puts("\nHello, hazelnut!\n");
    page_init();

    kprintf("Start to sleep ...\n");
    ksleep_millisec(36864000 * 2); // 10 seconds or so
    kprintf("Wake up!\n");

    user_init();
    int current_task = 0;

    while (1)
    {
        task_proceed(current_task);
        current_task = (current_task + 1) % _num_of_tasks;
    }

    while (1)
    {
        // never gonna reach here...
        uart_getchar();
    }
    return;
}
