#include "defs.h"

// void plic_set_priority(int id);

void plic_init(void)
{
    uint32 current_hart_id = read_tp();
    // set priority for UART0
    plic_set_priority(UART0_IRQ, 1);
    plic_set_m_enable(current_hart_id, UART0_IRQ);
    plic_set_m_threshold(current_hart_id, 0);

    return;
}
