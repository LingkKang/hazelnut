#include "types.h"
#include "defs.h"

// defined in memory.s
extern uint32 TEXT_START;
extern uint32 TEXT_END;
extern uint32 DATA_START;
extern uint32 DATA_END;
extern uint32 RODATA_START;
extern uint32 RODATA_END;
extern uint32 BSS_START;
extern uint32 BSS_END;
extern uint32 HEAP_START;
// extern uint32 HEAP_SIZE;
extern uint32 MEM_END;
#define HEAP_SIZE (MEM_END - HEAP_START)

#define PAGE_SIZE 4096

// page header description
#define OCCUPIED (1 << 0)  // bit 0, set to 1 if allocated
#define PAGE_TAIL (1 << 1) // bit 1, set to 1 if is last allocated chunck

struct Page
{
    uint8 profile;
};

static uint32 starting_point = 0; // where allocation starts
static uint32 terminal_point = 0; // where allocation ends
static uint32 page_count = 0;     // the number of pages that can be allocated

#define PGH_START HEAP_START                         // page header start
#define PGH_END (PGH_START + page_count * PAGE_SIZE) // page header end

#define _check_tail(page) (page.header & PAGE_TAIL)
#define _check_occupied(page) (page.header & OCCUPIED)
#define _clear(pg) (pg->profile = 0) // clean header to 0 as initialization
#define _align(addr) ((addr + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1))

void page_init()
{
    // reserve 8 pages to store page header info
    page_count = (HEAP_SIZE / PAGE_SIZE) - 8;
    kprintf("Heap starts at %x\n", HEAP_START);
    // kprintf("Memory end is %x\n", MEM_END);
    // kprintf("Heap size is %d\n", HEAP_SIZE);
    kprintf("Number of pages is %d\n", page_count);

    // clean headers of file
    struct Page *pg = (struct Page *)HEAP_START;
    for (int i = 0; i < page_count; i++)
    {
        _clear(pg);
        pg++;
    }

    // get allocation staring and ending locations
    starting_point = _align(HEAP_START + 8 * PAGE_SIZE);
    terminal_point = starting_point + (PAGE_SIZE * page_count);

    kprintf("TEXT:   0x%x -> 0x%x\n", TEXT_START, TEXT_END);
    kprintf("RODATA: 0x%x -> 0x%x\n", RODATA_START, RODATA_END);
    kprintf("DATA:   0x%x -> 0x%x\n", DATA_START, DATA_END);
    kprintf("BSS:    0x%x -> 0x%x\n", BSS_START, BSS_END);
    kprintf("HEAP:   0x%x -> 0x%x\n", starting_point, terminal_point);
}

void *kalloc(void)
{
    // allocate one page
    struct Page *p = (struct Page *)PGH_START;
    uint16 i = 0;
    while (i + PGH_START < PGH_END)
    {
        if (((p->profile) & OCCUPIED) == 0)
        {
            break;
        }
        i++;
        p++;
        if ((int)p > PGH_END)
        {
            return NULL;
        }
    }
    p->profile |= OCCUPIED;
    p->profile |= PAGE_TAIL;
    return (void *)(starting_point + PAGE_SIZE * i);
}

void *kalloc_pages(uint32 pg_num)
{
    // alloc multiple pages
    TODO();
    return NULL;
}

void kfree(void *p)
{
    TODO();
    return;
}

void test_alloc(void)
{
    kprintf("First  page allocated at %p\n", kalloc());
    kprintf("Second page allocated at %p\n", kalloc());
    kprintf("Third  page allocated at %p\n", kalloc());
    return;
}