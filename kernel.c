#include "defs.h"

/*
Main function of the kernel.
Basically register some user tasks and schedule around them.
*/
void kernel_main(void)
{
    // initialize user tasks
    user_init();

    // call scheduler to arrange them
    task_scheduler();

    while (1)
    {
        // never gonna reach here...
        uart_getchar();
    }
    return;
}
