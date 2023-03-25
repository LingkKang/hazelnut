
# void trap_init(void);
.func trap_init
.globl trap_init

trap_init:
    # save trap_vactor address to mtvec
    lw t0, trap_vector
    csrw mtvec, t0
    ret

.endfunc

.func trap_vector
.globl trap_vector
.align 4

trap_vector:
    # save context
    csrrw a0, mscratch, a0
    mv a1, a0
    call switch_context

    # call trap_handler
    csrr a0, mepc
    csrr a1, mcause
    call trap_handler

    # in case that return address was changed
    csrw mepc, a0

    # restore context
    csrr a0, mscratch
    mv a1, a0
    call switch_context

    mret

.endfunc

.end
