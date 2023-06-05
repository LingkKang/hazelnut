// serial port driver

#include "types.h"

// UART control registers
// defined only when needed
// see http://byterunner.com/16550.html
#define RHR 0 // Receive Holding Register (READ)
#define THR 0 // Transmit Holding Register (WRITE)
#define DLL 0 // Divisor Latch Least Significant Bit (WRITE)
#define DLM 1 // Divisor Latch Most Significant Bit (WRITE)
#define IER 1 // Interrupt Enable Register (WRITE)
#define LCR 3 // Line Control Register (WRITE)
#define LSR 5 // Line Status Register (READ)

// Special bits of registers
#define LCR_BAUD_LATCH (1 << 7) // 0 disabled (default), 1 enabled
#define LCR_WORD_LEN_8 3        // bit 0 and 1 both set to 1 for word length 8
#define LSR_TR_IDLE (1 << 5)    // 0 THR is empty, previous data transmitted
#define LSR_RX_READY 1          // first bit is 1 if RHR receives data

/* conventional abbreviations:
    RX: receive
    TX: transmit
*/

volatile uint8 *get_reg(int reg)
{
    // return the memory location of given register name
    return (volatile uint8 *)(reg + UART0);
}

void uart_write_reg(int reg, uint8 val)
{
    volatile uint8 *p = get_reg(reg);
    *p = val;
    return;
}

uint8 uart_read_reg(int reg)
{
    return *(get_reg(reg));
}

/*
Initialize the UART control register for basic I/O.
*/
void uart_init(void)
{
    // enable interrupts
    int ier = uart_read_reg(IER);
    ier = ier | (1 << 0);
    uart_write_reg(IER, ier);

    // set baud rate
    // first, change LCR's bit 7 to 1
    // make sure not to modify any other bits.
    uint8 current_LCR = uart_read_reg(LCR);
    uart_write_reg(LCR, current_LCR | LCR_BAUD_LATCH);
    // second, set divisor latch to 3
    // which makes baud rate 38.4K
    // separate to LSB and MSB
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

/*
Print a character on terminal via UART.
*/
void uart_putchar(char c)
{
    uint8 current_LSR;
    while (1)
    {
        current_LSR = uart_read_reg(LSR);
        if (current_LSR | LSR_TR_IDLE)
        {
            break;
        }
    }
    uart_write_reg(THR, c);
    return;
}

/*
Print a string on terminal via UART.
*/
void uart_puts(char *s)
{
    while (*s)
    {
        uart_putchar(*s);
        s++;
    }
    return;
}

/*
Print binary value of a given char.
Mainly used for testing.
*/
void uart_print_char_val(uint8 c)
{
    uint8 i = 7;
    while (1)
    {
        uint8 bit = ((c & (1 << i)) ? '1' : '0');
        uart_putchar(bit);
        if (i == 0)
        {
            break;
        }
        i--;
    }
    return;
}

/*
Read in a character from UART
and echo it back as feedback to user.
Basically waiting for instructions.
*/
uint8 uart_getchar(void)
{
    uint8 current_LSR = uart_read_reg(LSR);
    if (current_LSR & LSR_RX_READY)
    {
        uint8 c = uart_read_reg(RHR);

        // make input visible
        uart_putchar(c);
        // uart_print_char_val(c); // check binary of input
        if (c == '\r')
        {
            // handle carrige return new line
            uart_putchar('\n');
        }
        else if (c == '\b')
        {
            // handle backspace
            uart_puts(" \b"); // whitespace cover previous input
        }
        return c;
    }
    return -1;
}

/*
Read in a character but do not echo back.
Mainly for keyboard interruption.
*/
uint8 uart_read_char(void)
{
    if (uart_read_reg(LSR) & LSR_RX_READY)
    {
        uint8 c = uart_read_reg(RHR);
        return c;
    }
    return -1;
}

/*
When keyboard interrupt arise by UART,
read in all input from buffer and
echo back them one by one.
AKA UART interrupt handler.
*/
void uart_interrupt(void)
{
    while (1)
    {
        uint8 c = uart_read_char();
        if (c == 255) // unsigned char is 255 for -1
        {
            uart_putchar('\n');
            break;
        }
        else
        {
            uart_putchar(c);
        }
    }
    return;
}
