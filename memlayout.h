// physical memory layout

#ifndef __MEMLAYOUT_H__
#define __MEMLAYOUT_H__

// defined in QEMU
#define UART0 0x10000000
#define UART0_IRQ 10    // interrupt request id of uart0


// machine mode interrupt enable
#define MIE_MEIE (1 << 11) // external
#define MIE_MTIE (1 << 7)  // timer
#define MIE_MSIE (1 << 3)  // software


// core local interruption
#define CLINT 0x2000000
#define CLINT_MTIME (CLINT + 0xBFF8)
#define CLINT_MTIMECMP (CLINT + 0x4000)
#define CLINT_TIME_BASE_FREQ 10000000

#endif
