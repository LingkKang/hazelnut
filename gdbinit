# GDB initialization script

set disassemble-next-line on
b _start
b uart_init
target remote : 1234
c
