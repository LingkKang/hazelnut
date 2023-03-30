# read & write some registers

.text

.globl read_tp
# uint32 read_tp(void);
read_tp:
    mv          a0, t0
    ret

.end
