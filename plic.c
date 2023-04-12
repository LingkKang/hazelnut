#include "defs.h"

// void plic_set_priority(int id);

void plic_init(void)
{
    // set priority for UART0
    plic_set_priority(UART0_IRQ, 1);

    return;
}
