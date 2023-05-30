.DEFAULT_GOAL := all

ifeq ($(OS),Windows_NT)
# Windows-specific
PREFIX = riscv64-unknown-elf-
else ifeq ($(shell uname),Linux)
# Linux-specific
PREFIX = riscv64-unknown-linux-gnu-
else
    $(error Unsupported operating system: $(OS))
endif

GCC = ${PREFIX}gcc
C_FLAGS = -nostdlib -fno-builtin -march=rv32ima -mabi=ilp32 -g -Wall

QEMU = qemu-system-riscv32
QEMU_FLAGS = -nographic -machine virt -bios none

GDB = ${PREFIX}gdb

OBJDUMP = ${PREFIX}objdump

ASM_FILE =      \
	boot.s      \
	memory.s    \
	timer.s     \
	switch.s    \
	traps.s     \
	riscv.s

C_FILE =        \
	enter.c     \
	uart.c      \
	print.c     \
	page.c      \
	sched.c     \
	user.c      \
	kernel.c    \
	trap.c      \
	plic.c

OBJ_FILE = $(ASM_FILE:.s=.o)
OBJ_FILE += $(C_FILE:.c=.o)

all: os.elf

os.elf: ${OBJ_FILE}
	${GCC} ${C_FLAGS} -T kernel.ld -o $@ $^

%.o: %.S
	${GCC} ${C_FLAGS} -c -o $@ $^

%.o: %.s
	${GCC} ${C_FLAGS} -c -o $@ $^

%.o: %.c
	${GCC} ${C_FLAGS} -c -o $@ $^

run: all
	@echo Press Ctrl-A and then X to exit QEMU
	@echo ------------------------------------
	${QEMU} ${QEMU_FLAGS} -kernel os.elf

debug: all
	@echo Press Ctrl-A and then X to exit QEMU
	@echo ------------------------------------
	${QEMU} ${QEMU_FLAGS} -kernel os.elf -s -S 

gdb: all
	@echo Type 'quit' to exit GNU DGB
	@echo ---------------------------
	${GDB} os.elf -q -x gdbinit

disassemble: all
	@echo Check out disassembled code at `os.txt`
	${OBJDUMP} -D os.elf > os.txt

.PHONY: clean
clean:
	del *.o *.bin *.elf os.txt
