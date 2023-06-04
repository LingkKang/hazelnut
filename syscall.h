#include "types.h"

#ifndef __SYSCALL_H__
#define __SYSCALL_H__

#define SYSCALL_GET_HART_ID 1 // get hart id
#define SYSCALL_GET_HW_TIME 2 // get hardware time
#define SYSCALL_TASK_YIELD 3 // yield to OS

extern uint32 sys_get_hart_id(void);
extern uint32 sys_get_hw_time(void);
extern void sys_task_yield(void);

#endif // __SYSCALL_H__
