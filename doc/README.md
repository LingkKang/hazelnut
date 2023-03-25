# HazelNut Kernel

## Files

- `boot.S`: Bootstrap to load kernel.
- `enter.c`: Routines before going to kernel.
- `uart.c`: Serial port driver.
- `print.c`: Formatted print utilities.
- `memory.s`: Addresses receive from `kernel.ld`.
- `page.c`: Memory initialization, allocation and free.
- `timer.s`: Sleep for milliseconds (not accurate).
- `switch.s`: Context switch.
- `sched.c`: CPU Scheduling.
- `user.c`: User tasks.
- `kernel.c`: Kernel of HazelNut.
- `traps.s`: Trap (exception and interrupt) related (assembly side).
- `trap.c`: Trap handler.
