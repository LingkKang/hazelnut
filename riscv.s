# read & write some registers

.text

.globl read_mhartid
# uint32 read_mhartid(void);
read_mhartid:
    csrr        a0, mhartid
    ret

.globl read_tp
# uint32 read_tp(void);
read_tp:
    mv          a0, tp
    ret

.globl write_tp
# void write_tp(uint32);
write_tp:
    mv          tp, a0
    ret

.equ            PLIC, 0x0c000000

.globl plic_set_priority
# void plic_set_priority(uint32 irq_id, int pri_val);
    # IRQ: Interrupt Request
    # pri_val: priority value of interrupt source
plic_set_priority:
    li          t0, PLIC
    slli        a0, a0, 2
    add         a0, a0, t0
    sw          a1, 0(a0)
    ret

.end
