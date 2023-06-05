/*
Header file of system call
*/

#include "types.h"

#ifndef __SYSCALL_H__
#define __SYSCALL_H__

#define SYSCALL_GET_HART_ID 1 // get hart id
#define SYSCALL_GET_HW_TIME 2 // get hardware time
#define SYSCALL_TASK_YIELD 3  // yield the task to OS

/* syscall of get HART id. */
extern uint32 sys_get_hart_id(void);
/* syscall of get hardware time. */
extern uint32 sys_get_hw_time(void);
/* syscall of yield task itself to OS. */
extern void sys_task_yield(void);

#endif // __SYSCALL_H__
