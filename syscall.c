#include "defs.h"
#include "syscall.h"

void syscall_handler(Context *context)
{
    // TODO();
    regis syscall_id = context->a7;
    switch (syscall_id)
    {
    case SYSCALL_GET_HART_ID:
        context->a0 = read_mhartid();
        break;

    case SYSCALL_GET_HW_TIME:
        // context->a0 = 0;
        asm volatile("rdtime %0" : "=r" (context->a0));
        break;

    case SYSCALL_TASK_YIELD:
        task_yield();
        break;

    default:
        kprintf("Unknown syscall id %d\n", syscall_id);
        panic("");
        break;
    }
    return;
}
