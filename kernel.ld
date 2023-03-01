/* linker script for compiling */

/* specify architecture */
OUTPUT_ARCH("RISCV")

/* set entry point */
ENTRY(enter)

/* set location and size of memory block */
MEMORY
{
    ram (WXA!RI): ORIGIN = 0x80000000, LENGTH = 128M
}

/* integrate each section */
SECTIONS
{
    .text : {
        PROVIDE(_text_start = .);
        *(.text)
        PROVIDE(_text_end = .);
    } > ram

    .rodata : {
        PROVIDE(_rodata_start = .);
        *(.rodata)
        PROVIDE(_rodata_end = .);
    } > ram

    .data : {
        . = ALIGN(4069);
        PROVIDE(_data_start = .);
        *(.data)
        PROVIDE(_data_end = .);
    } > ram

    .bss : {
        PROVIDE(_bss_start = .);
        *(.bss)
        PROVIDE(_bss_end = .);
    } > ram

    PROVIDE(_memory_start = ORIGIN(ram));
    PROVIDE(_memory_end = ORIGIN(ram) + LENGTH(ram));

    PROVIDE(_heap_start = _bss_end);
    PROVIDE(_heap_size = _memory_end - _heap_start);
}