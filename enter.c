// enter to hazelnut kernel

#include "defs.h"

void enter(void)
{
    uart_init();
    uart_puts("\nHello, hazelnut!\n");
    while (1)
    {
        uart_getchar();
    }
}
