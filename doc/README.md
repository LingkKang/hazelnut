# HazelNut Kernel

## Files

- `boot.S`: Bootstrap to load kernel.
- `delay.c`: Delay a task in user mode.
- `enter.c`: Routines before going to kernel.
- `kernel.c`: Kernel of HazelNut.
- `lock.c`: Spin lock related.
- `memory.s`: Addresses receive from `kernel.ld`.
- `page.c`: Memory initialization, allocation and free.
- `plic.c`: Functions of platform level interrupt controller (PLIC).
- `print.c`: Formatted print utilities.
- `riscv.s`: Assembly code for reading and writing some registers.
- `sched.c`: CPU Scheduling.
- `switch.s`: Context switch.
- `syscall.c`: Handle all system call request.
- `syscalls.s`: Assembly interfaces of system calls.
- `timer.s`: Hardware timer and sleep for milliseconds (not accurate).
- `trap.c`: Trap handler.
- `traps.s`: Trap (exception and interrupt) related (assembly side).
- `uart.c`: Serial port driver.
- `user.c`: User tasks.
