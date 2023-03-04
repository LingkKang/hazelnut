// formatted print utilities: kprintf, panic

#include <stdarg.h>
#include "defs.h"

char digits[] = "0123456789ABCDEF";

void kprint_int(int num, int base)
{
    // print an integer, only support %d and %h
    if (base != 10 && base != 16)
    {
        panic("Unsupported number system!");
    }
    else if (num == 0)
    {
        uart_putchar('0');
        return;
    }
    if (num < 0)
    {
        if (base == 10)
        {
            uart_putchar('-');
            num = -num;
        }
        else
        {
            kprint_ptr(num);
            return;
        }
    }
    uint8 reverse_digits[32];
    int i = 0;
    while (num != 0)
    {
        reverse_digits[i] = digits[num % base];
        num /= base;
        i++;
    }
    i--;
    while (i >= 0)
    {
        uart_putchar(reverse_digits[i]);
        i--;
    }
    return;
}

void kprint_ptr(uint32 p)
{
    // print hex value of a pointer.
    uint8 digit;
    uint8 i = 7;
    uint32 four_bits;
    while (1)
    {
        four_bits = p & (15 << i * 4);
        digit = four_bits >> i * 4;
        uart_putchar(digits[digit]);
        if (i == 0)
        {
            break;
        }
        i--;
    }
    return;
}

void kprintf(char *s, ...)
{
    // printf, only support %d, %x, %p, %s and %c
    va_list args;
    va_start(args, s);
    int i = 0;
    uint8 c = s[i];
    while (c)
    {
        // break untill null char
        if (c != '%')
        {
            uart_putchar(c);
        }
        else
        {
            c = s[++i];
            switch (c)
            {
            case 'd':
                kprint_int(va_arg(args, int), 10);
                break;

            case 'x':
                kprint_int(va_arg(args, int), 16);
                break;

            case 'p':
                kprint_ptr(va_arg(args, uint32));
                break;

            case 's':
                uart_puts(va_arg(args, char *));
                break;

            case 'c':
                uart_putchar(va_arg(args, int));
                break;

            case '%':
                uart_putchar(c);
                break;

            default:
                panic("Unknown format specifier.");
                break;
            }
        }
        i++;
        c = s[i];
    }
}

void panic(char *s)
{
    uart_puts("\nPANIC @ ");
    uart_puts(s);
    uart_puts("\n");
    while (1)
        ;
    return;
}

void test_print(void)
{
    // kprint_ptr test
    kprint_ptr(2);
    uart_putchar('\n');
    kprint_ptr(15);
    uart_putchar('\n');
    kprint_ptr(0xABCD98);
    uart_putchar('\n');
    kprint_ptr(123456789); // 075B CD15
    uart_putchar('\n');
    kprint_ptr(4294967295); // FFFF FFFF
    uart_putchar('\n');

    // kprint_int test
    // base 10 part
    kprint_int(-235, 10);
    uart_putchar('\n');
    kprint_int(0xABCD, 10); // 43981
    uart_putchar('\n');
    kprint_int(987654321, 10);
    uart_putchar('\n');
    // base 16 part
    kprint_int(-3, 16); // FFFF FFFD
    uart_putchar('\n');
    kprint_int(0xABCD, 16);
    uart_putchar('\n');
    kprint_int(987654321, 16); // 3ADE 68B1
    uart_putchar('\n');

    // kprintf test
    kprintf("Blablabla\n");
    kprintf("Today is %d %s %d\n", 2022, "March", 4);
    kprintf("Function puts is at %p\n", uart_puts);
    kprintf("Number %d in hex is %x\n", 13579, 13579);
    kprintf("Test %c %% char...\n", 'a');
}
