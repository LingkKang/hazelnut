#include "defs.h"
#include "syscall.h"

/*
In machine mode, handle all syscall requests
and return control to trap handler.
*/
void syscall_handler(Context *context)
{
    regis syscall_id = context->a7;
    switch (syscall_id)
    {
    case SYSCALL_GET_HART_ID:
        context->a0 = read_mhartid();
        break;

    case SYSCALL_GET_HW_TIME:
        asm volatile(
            "rdtime %0"
            : "=r"(context->a0));
        break;

    case SYSCALL_TASK_YIELD:
        task_yield();
        break;

    default:
        kprintf("Unknown syscall id %d\n", syscall_id);
        panic("syscall_handler");
        break;
    }
    return;
}
