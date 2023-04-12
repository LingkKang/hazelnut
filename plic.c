#include "defs.h"

// void plic_set_priority(int id);

void plic_init(void)
{
    // set priority for UART0
    plic_set_priority(UART0_IRQ, 1);
    plic_set_m_enable(read_tp(), UART0_IRQ);

    return;
}
