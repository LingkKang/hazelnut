// enter to hazelnut kernel

#include "defs.h"

void enter(void)
{
    // do some initialization work

    // store each hart's hartid at tp register
    write_tp(read_mhartid());

    // uart initialization
    uart_init();
    uart_puts("\nHello, hazelnut!\n");

    // memory layout initialization
    page_init();

    // enable context switch
    sched_init();

    // set up trap handler
    trap_init();

    // PLIC initialization
    plic_init();

    // timer initialization
    timer_init();

    // initialization finished
    // hand out control to kernel
    kernel_main();
    return;
}
