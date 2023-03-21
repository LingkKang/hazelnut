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

trap_vector:
    nop
    nop
    ret

.endfunc

.end
