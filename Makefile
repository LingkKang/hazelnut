.DEFAULT_GOAL := all

AS = riscv64-unknown-elf-as
LD = riscv64-unknown-elf-ld
QEMU = qemu-system-riscv64

ASM = boot.S

all:
	${AS} ${ASM} -o boot.o
	${LD} boot.o -o boot.elf

run: all
	${QEMU} -machine virt -bios none -kernel boot.elf
