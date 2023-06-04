# RISC-V boot of hazelnut

.globl _start

.equ            STACK_SIZE, 1024
.equ            CPU_NUM, 8

.section .text

_start:
    csrr        t0, mhartid                 # put current hart id into t0
    bnez        t0, pend                    # branching if not zero (first) hart

    slli        t0, t0, 10                  # logic shift to left 10 bits
    la          sp, stacks + STACK_SIZE     # initially sp points to the end of stacks
    add         sp, sp, t0                  # let sp points to hart's stack accrodingly

    li          t0, 0xffffffff
    csrw        pmpaddr0, t0
    li          t0, 0xf
    csrw        pmpcfg0, t0

    li          t0, 1 << 7
    csrr        a1, mstatus
    or          t0, t0, a1
    csrw        mstatus, t0

    j           enter                       # enter to kernel, defined in enter.c

stacks:
    .space      STACK_SIZE * CPU_NUM        # space allocated for stacks

pend:
    # pending other hearts
    wfi                                     # wait for instruction
    j           pend

.end                                        # end of file
