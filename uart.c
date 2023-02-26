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

// Special bits of registers
#define LCR_BAUD_LATCH (1 << 7) // 0 disabled (default), 1 enabled
#define LCR_WORD_LEN_8 3 // bit 0 and 1 both set to 1 for word length 8

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

void uart_init(void) {
    // Initialize the UART control register

    // disable interrupts
    uart_write_reg(IER, 0x00);

    // set baud rate 
    // first, change LCR's bit 7 to 1
    // make sure not to modify any other bits.
    uint8 current_LCR = uart_read_reg(LCR);
    uart_write_reg(LCR, current_LCR | LCR_BAUD_LATCH);
    // second, set divisor latch to 3
    // which makes baud rate 38.4K
    // seprate to LSB and MSB
    uart_write_reg(DLL, 0x03);
    uart_write_reg(DLM, 0x00);

    // set asynchronous data communication format
    // by set LCR's bits
    // 8 bits word length without parity
    uint8 new_LCR = 0;
    new_LCR |= LCR_WORD_LEN_8;
    uart_write_reg(LCR, new_LCR);

    return;
}

void uart_putchar(char c);
void uart_puts(char *s);
