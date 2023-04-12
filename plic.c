#include "defs.h"

// mie, machine mode interrupt enable register
#define MIE_MEIE (1 << 11) // external interrupt

// mstatus, machine status register
#define MSTATUS_MIE (1 << 3) // mie inside mstatus


void plic_init(void)
{
    // initialize Platform Level Interrupt Controller

    uint32 current_hart_id = read_tp();

    plic_set_m_threshold(current_hart_id, 0);

    // set priority for UART0
    plic_set_priority(UART0_IRQ, 1);
    plic_set_m_enable(current_hart_id, UART0_IRQ);

    // enable machine mode external interrupts
    write_mie(read_mie() | MIE_MEIE);

    // enable machine mode global interrupts
    write_mstatus(read_mstatus() | MSTATUS_MIE);
    return;
}


int plic_claim(void)
{
    return plic_m_claim(read_tp());
}


void plic_complete(int irq_id)
{
    plic_m_complete(read_tp(), irq_id);
    return;
}
