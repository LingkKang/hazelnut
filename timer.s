# RISC-V 32 sleep function

# void ksleep_millisec(unsigned int t);

.func ksleep_millisec
.globl ksleep_millisec

ksleep_millisec:
    rdtime t0           # time starts to sleep

.L0:
    nop
    nop
    rdtime t1           # current time in loop
    sub t1, t1, t0      # t1 = t1 - t0
    bgeu t1, a0, .L1    # if t1 >= a0, return
    j .L0

.L1:
    ret

.endfunc
.end
