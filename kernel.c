#include "defs.h"

void kernel_main(void)
{

    // initialize user tasks
    user_init();
    int current_task = 0;

    // go on and run tasks
    while (1)
    {
        task_proceed(current_task);
        // take turns
        current_task = (current_task + 1) % _num_of_tasks;
    }

    while (1)
    {
        // never gonna reach here...
        uart_getchar();
    }
    return;
}
