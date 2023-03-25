#include "defs.h"

regis trap_handler(regis mepc, regis mcause)
{
    // handle kernel traps
    // not expose to other scope

    kprintf("Start to handle the trap!\n");

    int trap_type = mcause >> 31;
    if (trap_type == 1)
    {
        // MSB of `mcause` is 1, interrupt
        kprintf("\tTrap type: Interrupt\n");
    }
    else
    {
        // MSB of `mcause` is 0, exception
        kprintf("\tTrap type: Exception\n");
    }

    regis trap_code = (mcause << 1) >> 1;
    kprintf("\tTrap code: %d\n", trap_code);
    regis rpc = mepc;

    if (trap_type)
    {
        // handle interrupts
        panic("Unhandled interrupt!\n");
    }
    else
    {
        switch (trap_code)
        {
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

void test_exception(void)
{
    kprintf("Going to have an exception!\n");
    // try to assign value pointed by NULL
    *(int *)NULL = 1;
    kprintf("Exception handled successfully!\n");
    return;
}
