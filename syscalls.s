.equ        SYSCALL_GET_HART_ID, 1
.equ        SYSCALL_DELAY, 2

.globl get_hart_id
.func get_hart_id
get_hart_id:
    li      a7, SYSCALL_GET_HART_ID
    ecall

    ret

.endfunc

.end
