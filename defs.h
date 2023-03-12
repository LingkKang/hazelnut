// ultimate header file

#include "types.h"

#define TODO(void) (panic("TODO"))

// uart.c
extern void uart_init(void);
extern void uart_putchar(char c);
extern void uart_puts(char *s);
extern uint8 uart_getchar(void);

// print.c
extern void kprint_int(int num, int base);
extern void kprint_ptr(uint32 p);
extern void panic(char *s);
extern void kprintf(char *s, ...);

// page.c
extern void page_init(void);
