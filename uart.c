#include "types.h"

#define UART0 0x10000000 // memory address of UART0

// Register bit maps of UART
#define RHR 0
#define THR 0
#define IER 1
#define CFR 2
#define ISR 2
#define LCR 3
#define MCR 4
#define LSR 5
#define MSR 6
#define SPR 7

volatile uint8_t get_reg(int reg);
void uart_init(void);
void uart_putchar(char c);
void uart_puts(char *s);
