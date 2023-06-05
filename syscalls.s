# All system calls
# basically put syscall id at `a7` as convention

.equ        SYSCALL_GET_HART_ID, 1
.equ        SYSCALL_GET_HW_TIME, 2
.equ        SYSCALL_TASK_YIELD, 3


.func sys_get_hart_id
.globl sys_get_hart_id
# uint32 sys_get_hart_id(void);
sys_get_hart_id:
    li      a7, SYSCALL_GET_HART_ID
    ecall

    ret
.endfunc


.func sys_get_hw_time
.globl sys_get_hw_time
# uint32 sys_get_hw_time(void);
sys_get_hw_time:
    li      a7, SYSCALL_GET_HW_TIME
    ecall

    ret
.endfunc


.func sys_task_yield
.globl sys_task_yield
# void sys_task_yield(void);
sys_task_yield:
    li      a7, SYSCALL_TASK_YIELD
    ecall

    ret
.endfunc

.end
