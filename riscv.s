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

.end
