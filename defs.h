/* ultimate header file */

#ifndef __DEFS_H__
#define __DEFS_H__

#include "types.h"
#include "asm_defs.h"
#include "syscall.h"

#define TRUE 1
#define FALSE 0
#define NULL 0

#define TODO(void) (panic("TODO")) // Unimplemented panic

// uart.c

extern void uart_init(void);
extern void uart_putchar(char c);
extern void uart_puts(char *s);
extern void uart_print_char_val(uint8 c);
extern uint8 uart_getchar(void);
extern void uart_interrupt(void);

// print.c

extern void kprint_int(int num, int base);
extern void kprint_ptr(uint32 p);
extern void kprintf(char *s, ...);
extern void panic(char *s);

// page.c

extern void page_init(void);
extern void *kalloc(void);
extern void *kalloc_pages(uint32 pg_num);
extern void kfree(void *p);

// sched.c

extern void sched_init(void);
extern int task_create(void *routine_entry);
extern int _num_of_tasks;
extern int _current_task;
extern void task_yield(void);
extern void task_scheduler(void);

// user.c

extern void user_init(void);

// kernel.c

extern void kernel_main(void);

// trap.c

regis trap_handler(regis mepc, regis mcause, Context context);
extern void test_exception(void);
extern void external_interrupt_handler(void);
extern void software_interrupt_handler(void);

// plic.c

extern void plic_init(void);
extern int plic_claim(void);
extern void plic_complete(int irq_id);

// lock.c

void init_lock(SpinLock *lock);
extern void acquire_lock(SpinLock *lock);
void release_lock(SpinLock *lock);

// syscall.c

void syscall_handler(Context *context);

// delay.c

void delay(int time);

#endif // __DEFS_H__
