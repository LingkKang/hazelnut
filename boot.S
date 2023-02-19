# RISC-V boot loader of hazelnut

.globl _start

loop:
    j loop       # jump to loop label unconditionally

.section .text
_start:
    jal loop     # jump and link to loop label

    # pad the remaining bytes with zeros
    .fill 14 - (. - _start)
    .word 0x0
