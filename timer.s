.text

.equ            CLINT, 0x2000000
.equ            CLINT_MTIME, CLINT + 0xBFF8
.equ            CLINT_MTIMECMP, CLINT + 0x4000
# 10000000 ticks per second
.equ            CLINT_TIME_BASE_FREQ, 10000000

# void timer_load(int delta);
.func timer_load
.globl timer_load

timer_load:
    # set value in mtimercmp register

    # get current time
    li          t0, CLINT_MTIME             # t0 is address of mtime (lower bits)
    lw          s0, 0(t0)                   # value of current time (lower bits)
    li          t0, CLINT_MTIME
    lw          s1, 4(t0)                   # value of current time (higher bits)

    # get value to store at mtimecmp
    # value is mtime + delta
    mv          t0, s0
    add         s0, s0, a0                  # value should be set to mtimecmp
    sltu        t1, s0, t0
    add         s1, s1, t1

    # save value to the stack
    addi        sp, sp, -4
    sw          ra, 0(sp)

    # get mhartid
    call        read_mhartid                # hartid saved at a0

    # find address of mtimecmp
    slli        a0, a0, 3                   # hartid * 8
    li          t0, CLINT_MTIMECMP
    add         a0, a0, t0
    sw          s0, 0(a0)
    sw          s1, 4(a0)
    lw          ra, 0(a0)
    addi        sp, sp, 4

    ret
.endfunc


.equ            MIE_MTIE, 1 << 7
# void timer_init(void);
.func timer_init
.globl timer_init
timer_init:
    addi        sp, sp, -4
    sw          ra, 0(sp)

    # set time interval
    li          a0, CLINT_TIME_BASE_FREQ
    call        timer_load

    # enable machine mode timer interrupts
    call        read_mie
    li          t0, MIE_MTIE
    or          a0, a0, t0
    call        write_mie

    lw          ra, 0(sp)
    add         sp, sp, 4

    ret
.endfunc


# void ksleep_millisec(unsigned int t);

.func ksleep_millisec
.globl ksleep_millisec

ksleep_millisec:
    rdtime      t0                          # time starts to sleep

.L0:
    nop
    nop
    rdtime      t1                          # current time in loop
    sub         t1, t1, t0                  # t1 = t1 - t0
    bgeu        t1, a0, .L1                 # if t1 >= a0, return
    j           .L0

.L1:
    ret

.endfunc
.end
