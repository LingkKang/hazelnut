# HazelNut Kernel

## Files

- `boot.S`: Bootstrap to load kernel.
- `enter.c`: Routines before going to kernel.
- `kernel.c`: Kernel of HazelNut.
- `memory.s`: Addresses receive from `kernel.ld`.
- `page.c`: Memory initialization, allocation and free.
- `plic.c`: Functions of platform level interrupt controller (PLIC).
- `print.c`: Formatted print utilities.
- `riscv.s`: Assembly code for reading and writing some registers.
- `sched.c`: CPU Scheduling.
- `switch.s`: Context switch.
- `timer.s`: Sleep for milliseconds (not accurate).
- `trap.c`: Trap handler.
- `traps.s`: Trap (exception and interrupt) related (assembly side).
- `uart.c`: Serial port driver.
- `user.c`: User tasks.
