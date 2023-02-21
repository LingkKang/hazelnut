# RISC-V boot of hazelnut

.globl _start

.section .text

_start:
    csrr t0, mhartid  # put current hart id into t0
    bnez t0, pend     # branching if not zero (first) hart
    j end             # jump to end

end:
    j end             # jump to end label unconditionally

pend:
    wfi               # wait for instruction
    j pend

.end                  # end of file
