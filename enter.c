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
    while (1)
    {
        uart_getchar();
    }
}
