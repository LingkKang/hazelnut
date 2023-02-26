#include "types.h"

#define UART0 0x10000000 // memory address of UART0

// UART control registers
// defined only when needed
#define RHR 0
#define THR 0
#define DLL 0 // Divisor Latch Least Significant Bit (WRITE)
#define DLM 1 // Divisor Latch Most Significant Bit (WRITE)
#define IER 1 // Interrupt Enable Register (WRITE)
#define CFR 2
#define ISR 2
#define LCR 3 // Line Control Register (WRITE)
#define MCR 4
#define LSR 5
#define MSR 6
#define SPR 7

volatile uint8 *get_reg(int reg) {
    // return the memory location of given register name
    return (volatile uint8 *)(reg + UART0);
}

void uart_write_reg(int reg, uint8 val) {
    volatile uint8 *p = get_reg(reg);
    *p = val;
    return;
}

uint8 uart_read_reg(int reg) {
    return *(get_reg(reg));
}

void uart_init(void);
void uart_putchar(char c);
void uart_puts(char *s);
