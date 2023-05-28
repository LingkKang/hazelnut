#include "defs.h"

void kernel_main(void)
{

    // initialize user tasks
    user_init();

    // call scheduler to arrange them
    task_scheduler(0);

    while (1)
    {
        // never gonna reach here...
        uart_getchar();
    }
    return;
}
