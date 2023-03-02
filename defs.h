// ultimate header file

#include "types.h"

// uart.c
extern void uart_init(void);
extern void uart_putchar(char c);
extern void uart_puts(char *s);
extern uint8 uart_getchar(void);

// print.c
extern void panic(char *s);
extern void kprintf();