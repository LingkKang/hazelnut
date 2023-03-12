// enter to hazelnut kernel

#include "defs.h"

void enter(void)
{
    uart_init();
    uart_puts("\nHello, hazelnut!\n");
    page_init();
    while (1)
    {
        uart_getchar();
    }
}
