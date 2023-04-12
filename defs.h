// ultimate header file

#ifndef __DEFS_H__
#define __DEFS_H__

#include "types.h"

#define TRUE 1
#define FALSE 0
#define NULL 0

#define TODO(void) (panic("TODO"))

// uart.c
extern void uart_init(void);
extern void uart_putchar(char c);
extern void uart_puts(char *s);
extern uint8 uart_getchar(void);

// print.c
extern void kprint_int(int num, int base);
extern void kprint_ptr(uint32 p);
extern void panic(char *s);
extern void kprintf(char *s, ...);

// page.c
extern void page_init(void);
extern void *kalloc(void);
extern void *kalloc_pages(uint32 pg_num);
extern void kfree(void *p);

// timer.s
extern void ksleep_millisec(unsigned int t);

// switch.s
extern void switch_context(Context *old_context, Context *new_context);
extern void sched_init(void);

// sched.c
extern void task_proceed(int i);
extern int task_create(void *routine_entry);
extern void task_pause(void);
extern int _num_of_tasks;

// user.c
extern void user_init(void);

// kernel.c
extern void kernel_main(void);

// traps.s
extern void trap_init(void);

// trap.c
extern void test_exception(void);

// riscv.s
extern uint32 read_mhartid(void);
extern uint32 read_tp(void);
extern void write_tp(uint32);
uint32 read_mie(void);
void write_mie(uint32);
uint32 read_mstatus(void);
void write_mstatus(uint32);
extern void plic_set_priority(uint32 irq_id, int pri_val);
extern void plic_set_m_enable(uint32 hartid, uint32 irq_id);
extern void plic_set_m_threshold(uint32 hartid, int thr_val);
extern int plic_m_claim(uint32 hartid);
extern void plic_m_complete(uint32 hartid, uint32 irq_id);

// plic.c
extern void plic_init(void);
extern int plic_claim(void);
extern void plic_complete(int irq_id);

#endif
