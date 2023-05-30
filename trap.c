#include "defs.h"

/*
Analyze and handle traps.
Privileged operations which can not be exposed to user.
*/
regis trap_handler(regis mepc, regis mcause)
{
    // kprintf("Start to handle the trap!\n");

    int trap_type = mcause >> 31;
    // if (trap_type == 1)
    // {
    //     // MSB of `mcause` is 1, interrupt
    //     kprintf("\tTrap type: Interrupt\n");
    // }
    // else
    // {
    //     // MSB of `mcause` is 0, exception
    //     kprintf("\tTrap type: Exception\n");
    // }

    regis trap_code = (mcause << 1) >> 1;
    // kprintf("\tTrap code: %d\n", trap_code);
    regis rpc = mepc;

    if (trap_type)
    {
        // handle interrupts
        switch (trap_code)
        {
        case 3:
            // kprintf("Machine software interruption!\n");
            software_interrupt_handler();
            break;

        case 7:
            // kprintf("Machine timer interruption!\n");
            timer_interrupt_handler();
            break;

        case 11:
            uart_puts("External interruption!\n");
            external_interrupt_handler();
            break;

        default:
            panic("Unhandled interrupt!\n");
            break;
        }
    }

    else
    {
        // handle exceptions
        switch (trap_code)
        {
        case 1:
            kprintf("Instruction access fault!\n");
            kprintf("PC is at %p", rpc);
            panic("...");
            break;

        case 5:
            kprintf("Load access fault!\n");
            rpc += 4; // skip the instruction
            break;

        case 7:
            kprintf("Store/AMO access fault!\n");
            rpc += 4; // skip the instruction
            break;

        default:
            panic("Unhandled exception!\n");
            break;
        }
    }

    return rpc;
}

/*
Handle external interruption.
*/
void external_interrupt_handler(void)
{
    int irq_id = plic_claim();
    kprintf("External interrupt source %d\n", irq_id);
    if (irq_id == UART0_IRQ)
    {
        uart_interrupt();
    }
    else
    {
        panic("Unexpected interrupt!\n");
    }
    plic_complete(irq_id);
    return;
}

/*
Handle software interrupt,
AKA cooperative multitasking.
*/
void software_interrupt_handler(void)
{
    write_clint_msip_zero(read_mhartid());
    task_scheduler(TRUE);
}

/*
A test case of exception handling.
*/
void test_exception(void)
{
    kprintf("Going to have an exception!\n");
    // try to assign value pointed by NULL
    *(int *)NULL = 1;
    kprintf("Exception handled successfully!\n");
    return;
}
