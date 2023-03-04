// formatted print utilities: kprintf, panic

#include "defs.h"

char digits[] = "0123456789ABCDEF";

void kprintint(int num, int base)
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
            kprintptr(num);
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

void kprintptr(uint32 p)
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

void kprintf()
{
    TODO();
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
    // kprintptr test
    kprintptr(2);
    uart_putchar('\n');
    kprintptr(15);
    uart_putchar('\n');
    kprintptr(0xABCD98);
    uart_putchar('\n');
    kprintptr(123456789); // 075B CD15
    uart_putchar('\n');
    kprintptr(4294967295); // FFFF FFFF
    uart_putchar('\n');

    // kprintint test
    // base 10 part
    kprintint(-235, 10);
    uart_putchar('\n');
    kprintint(0xABCD, 10); // 43981
    uart_putchar('\n');
    kprintint(987654321, 10);
    uart_putchar('\n');
    // base 16 part
    kprintint(-3, 16); // FFFF FFFD
    uart_putchar('\n');
    kprintint(0xABCD, 16);
    uart_putchar('\n');
    kprintint(987654321, 16); // 3ADE 68B1
    uart_putchar('\n');

    // kprintf test
    kprintf("ABCD");
}