// formatted print utilities: kprintf, panic

#include "defs.h"

#define TODO(void) (panic("TODO"))

char digits[] = "0123456789ABCDEF";

void kprintint(int num)
{
    if (num < 0)
    {
        uart_putchar('-');
        num = -num;
    }
    else if (num == 0)
    {
        uart_putchar('0');
        return;
    }
    uint8 reverse_digits[32];
    int i = 0;
    while (num > 0)
    {
        reverse_digits[i] = digits[num % 10];
        num /= 10;
        i++;
    }
    i--;
    while (i >= 0) {
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
    uart_puts("0x");
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
    kprintint(8);
    uart_putchar('\n');
    kprintint(-235);
    uart_putchar('\n');
    kprintint(0xABCD);
    uart_putchar('\n');
    kprintint(987654321);
    uart_putchar('\n');
}