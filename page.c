#include "types.h"

// defined in memory.s
extern uint32 TEXT_STRAT;
extern uint32 TEXT_END;
extern uint32 DATA_START;
extern uint32 DATA_END;
extern uint32 RODATA_START;
extern uint32 RODATA_END;
extern uint32 BSS_START;
extern uint32 BSS_END;
extern uint32 HEAP_START;
extern uint32 HEAP_SIZE;

#define PAGE_SIZE 4096
#define PAGE_ORDER 12
