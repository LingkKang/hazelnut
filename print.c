// formatted print utilities: kprintf, panic

#include "defs.h"

#define TODO(void) (panic("TODO"))

void kprintf()
{
    TODO();
}

void panic(char *s)
{
    uart_puts("\nPANIC @ ");
    uart_puts(s);
    uart_puts("\n");
    while (1)
        ;
}
