# HazelNut Kernel

## Files

- `boot.S`: Bootstrap to load kernel.
- `enter.c`: Routines before going to kernel.
- `uart.c`: Serial port driver.
- `print.c`: Formatted print utilities.
- `memory.s`: Addresses receive from `kernel.ld`.
- `page.c`: Memory initialization, allocation and free.
