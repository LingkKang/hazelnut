.section .rodata
.globl HEAP_START
HEAP_START: .word _heap_start

# .globl Heap_SIZE
# Heap_SIZE: .word _heap_size

.globl MEM_END
MEM_END: .word _memory_end

.globl TEXT_START
TEXT_START: .word _text_start

.globl TEXT_END
TEXT_END: .word _text_end

.globl DATA_START
DATA_START: .word _data_start

.globl DATA_END
DATA_END: .word _data_end

.globl RODATA_START
RODATA_START: .word _rodata_start

.globl RODATA_END
RODATA_END: .word _rodata_end

.globl BSS_START
BSS_START: .word _bss_end

.globl BSS_END
BSS_END: .word _bss_end
