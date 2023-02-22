.DEFAULT_GOAL := all

AS = riscv64-unknown-elf-as
LD = riscv64-unknown-elf-ld
GCC = riscv64-unknown-elf-gcc
CFLAGS = -nostdlib -g -Ttext=0x80000000
QEMU = qemu-system-riscv64

ASM = boot.S

all:
	${AS} ${ASM} -o boot.o
	${GCC} -c -o enter.o enter.c
	${LD} ${CFLAGS} boot.o enter.o -o boot.elf

run: all
	${QEMU} -machine virt -bios none -kernel boot.elf

.PHONY: clean
clean:
	del *.o *.bin *.elf
