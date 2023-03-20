// enter to hazelnut kernel

#include "defs.h"

void enter(void)
{
    uart_init();
    uart_puts("\nHello, hazelnut!\n");
    page_init();
    sched_init();

    // initialization finished
    // hand out control to kernel
    kernel_main();
    return;
}
