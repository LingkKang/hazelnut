# read & write some registers

.text

.func read_mhartid
.globl read_mhartid
# uint32 read_mhartid(void);
read_mhartid:
    csrr        a0, mhartid
    ret
.endfunc


.func read_tp
.globl read_tp
# uint32 read_tp(void);
read_tp:
    mv          a0, tp
    ret
.endfunc


.func write_tp
.globl write_tp
# void write_tp(uint32);
write_tp:
    mv          tp, a0
    ret
.endfunc


.func read_mie
.globl read_mie
# uint32 read_mie(void);
read_mie:
    csrr        a0, mie
    ret
.endfunc


.func write_mie
.globl write_mie
# void write_mie(uint32);
write_mie:
    csrw        mie, a0
    ret
.endfunc


.func read_mstatus
.globl read_mstatus
# uint32 read_mstatus(void);
read_mstatus:
    csrr        a0, mstatus
    ret
.endfunc


.func write_mstatus
.globl write_mstatus
# void write_mstatus(uint32);
write_mstatus:
    csrw        mstatus, a0
    ret
.endfunc


# PLIC related functions 
# see qemu/include/hw/riscv/virt.h

.equ            PLIC, 0x0c000000

.func plic_set_priority
.globl plic_set_priority
# void plic_set_priority(uint32 irq_id, int pri_val);
    # IRQ: Interrupt Request
    # pri_val: priority value of interrupt source
        # 0: do not interrupt
        # 1: lowest priority
        # 7: highest priority
plic_set_priority:
    li          t0, PLIC
    slli        a0, a0, 2
    add         a0, a0, t0
    sw          a1, 0(a0)
    ret
.endfunc


.equ            M_ENABLE, PLIC + 0x2000

.func plic_set_m_enable
.globl plic_set_m_enable
# void plic_set_m_enable(uint32 hartid, uint32 irq_id);
# address: 
    # M_ENABLE + hartid * 0x80 
# value of address: 1 bit for one interrupt source
    # 1 enable
    # 0 disable
plic_set_m_enable:
    li          t0, 0x80
    mul         a0, a0, t0
    li          t0, M_ENABLE
    add         a0, a0, t0
    li          t0, 1
    sll         a1, t0, a1
    sw          a1, 0(a0)
    ret
.endfunc


.equ            M_THRESHOLD, PLIC + 0x200000

.func plic_set_m_threshold
.globl plic_set_m_threshold
# void plic_set_m_threshold(uint32 hartid, int thr_val);
# address: 
    # M_THRESHOLD + hartid * 0x1000
# any interrupt priority higher than thr_val will be handled by the hart
plic_set_m_threshold:
    li          t0, 0x1000
    mul         a0, a0, t0
    li          t0, M_THRESHOLD
    add         a0, a0, t0
    sw          a1, 0(a0)
    ret
.endfunc


.equ            M_CLAIM, PLIC + 0x200004

.func plic_m_claim
.globl plic_m_claim
# int plic_m_claim(uint32 hartid);
plic_m_claim:
    li          t0, 0x1000
    mul         a0, a0, t0
    li          t0, M_CLAIM
    add         a0, a0, t0
    lw          t0, 0(a0)
    mv          a0, t0
    ret
.endfunc


.equ            M_COMPLETE, M_CLAIM

.func plic_m_complete
.globl plic_m_complete
# extern void plic_m_complete(uint32 hartid, uint32 irq_id);
plic_m_complete:
    li          t0, 0x1000
    mul         a0, a0, t0
    li          t0, M_COMPLETE
    add         a0, a0, t0
    sw          a1, 0(a0)
    ret
.endfunc

.end
