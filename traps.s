
# void trap_init(void);
.func trap_init
.globl trap_init

trap_init:
    # initialize trap functionality

    # save `trap_vector` address to `mtvec` by `t0`
    lui         t0, %hi(trap_vector)        # load upper 20 bits
    addi        t0, t0, %lo(trap_vector)    # load lower 12 bits
    csrw        mtvec, t0 

    ret

.endfunc

.macro store_regs base
    sw          ra, 0(\base)
    sw          sp, 4(\base)
    sw          gp, 8(\base)
    sw          tp, 12(\base)
    sw          t0, 16(\base)
    sw          t1, 20(\base)
    sw          t2, 24(\base)
    sw          s0, 28(\base)
    sw          s1, 32(\base)
    sw          a0, 36(\base)
    sw          a1, 40(\base)
    sw          a2, 44(\base)
    sw          a3, 48(\base)
    sw          a4, 52(\base)
    sw          a5, 56(\base)
    sw          a6, 60(\base)
    sw          a7, 64(\base)
    sw          s2, 68(\base)
    sw          s3, 72(\base)
    sw          s4, 76(\base)
    sw          s5, 80(\base)
    sw          s6, 84(\base)
    sw          s7, 88(\base)
    sw          s8, 92(\base)
    sw          s9, 96(\base)
    sw          s10, 100(\base)
    sw          s11, 104(\base)
    sw          t3, 108(\base)
    sw          t4, 112(\base)
    sw          t5, 116(\base)
    sw          t6, 120(\base)
.endm

.macro load_regs base
    lw          ra, 0(\base)
    lw          sp, 4(\base)
    lw          gp, 8(\base)
    lw          tp, 12(\base)
    lw          t0, 16(\base)
    lw          t1, 20(\base)
    lw          t2, 24(\base)
    lw          s0, 28(\base)
    lw          s1, 32(\base)
    lw          a0, 36(\base)
    lw          a1, 40(\base)
    lw          a2, 44(\base)
    lw          a3, 48(\base)
    lw          a4, 52(\base)
    lw          a5, 56(\base)
    lw          a6, 60(\base)
    lw          a7, 64(\base)
    lw          s2, 68(\base)
    lw          s3, 72(\base)
    lw          s4, 76(\base)
    lw          s5, 80(\base)
    lw          s6, 84(\base)
    lw          s7, 88(\base)
    lw          s8, 92(\base)
    lw          s9, 96(\base)
    lw          s10, 100(\base)
    lw          s11, 104(\base)
    lw          t3, 108(\base)
    lw          t4, 112(\base)
    lw          t5, 116(\base)
    lw          t6, 120(\base)
.endm

.func trap_vector
.globl trap_vector
.align 4

trap_vector:
    # save context
    # mscratch is a pointer holds the address of contexts
    csrrw       t6, mscratch, t6

    # save the registers.
    store_regs  t6

    mv          t5, t6
    csrr        t6, mscratch
    sw          t6, 120(t5)

    # save a copy of mepc
    csrr        a0, mepc
    sw          a0, 124(t5) 

    # restore the context pointer
    csrw        mscratch, t5

    # call trap_handler
    csrr        a1, mcause
    call        trap_handler

    # in case that return address was changed
    csrw        mepc, a0

    # restore context
    csrr        t6, mscratch
    load_regs   t6

    mret

.endfunc

.end
