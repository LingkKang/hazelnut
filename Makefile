.DEFAULT_GOAL := all

PREFIX = riscv64-unknown-elf-

GCC = ${PREFIX}gcc
C_FLAGS = -nostdlib -fno-builtin -march=rv32ima -mabi=ilp32 -g -Wall

QEMU = qemu-system-riscv32
QEMU_FLAGS = -nographic -machine virt -bios none

GDB = ${PREFIX}gdb

ASM_FILE = \
	boot.S \
	memory.s \
	timer.s \
	switch.s

C_FILE = \
	enter.c \
	uart.c \
	print.c \
	page.c

OBJ_FILE = $(ASM_FILE:.S=.o)
OBJ_FILE += $(C_FILE:.c=.o)

all: os.elf

os.elf: ${OBJ_FILE}
	${GCC} ${C_FLAGS} -T kernel.ld -o $@ $^

%.o: %.S
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

gdb:
	@echo Type 'quit' to exit GNU DGB
	@echo ---------------------------
	${GDB} os.elf -q -x gdbinit

.PHONY: clean
clean:
	del *.o *.bin *.elf
