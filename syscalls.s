.equ        SYSCALL_GET_HART_ID, 1
.equ        SYSCALL_GET_HW_TIME, 2
.equ        SYSCALL_TASK_YIELD, 3

.globl sys_get_hart_id
.func sys_get_hart_id
sys_get_hart_id:
    li      a7, SYSCALL_GET_HART_ID
    ecall

    ret
.endfunc

.globl sys_get_hw_time
.func sys_get_hw_time
sys_get_hw_time:
    li      a7, SYSCALL_GET_HW_TIME
    ecall

    ret
.endfunc

.globl sys_task_yield
.func sys_task_yield
sys_task_yield:
    li      a7, SYSCALL_TASK_YIELD
    ecall

    ret
.endfunc

.end
