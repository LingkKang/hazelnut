/*
Declaration of functions from assembly file
*/

#ifndef __ASM_DEFS_H__
#define __ASM_DEFS_H__

#include "types.h"

// timer.s

/* Set value in `mtimercmp` register. */
extern void timer_load(int delta); 
/* Initialize timer. */
extern void timer_init(void);
/* Handle timer interruption. AKA preemptive multitasking. */
extern void timer_interrupt_handler(void);
/* Sleep / delay for given time of milliseconds. */
extern void ksleep_millisec(unsigned int t);


// switch.s

/* Switch to / restore the given context. */
extern void switch_to(Context *next);
/* Start a new user task. */
extern void start_task(Context *next);


// traps.s

/* Initialize trap functionality. */
extern void trap_init(void);


// riscv.s

extern uint32 read_mhartid(void);
extern uint32 read_tp(void);
extern void write_tp(uint32);
extern uint32 read_mie(void);
extern void write_mie(uint32);
extern uint32 read_mstatus(void);
extern void write_mstatus(uint32);
extern uint32 read_mscratch(void);
extern void write_mscratch(uint32);
extern void plic_set_priority(uint32 irq_id, int pri_val);
extern void plic_set_m_enable(uint32 hartid, uint32 irq_id);
extern void plic_set_m_threshold(uint32 hartid, int thr_val);
extern int plic_m_claim(uint32 hartid);
extern void plic_m_complete(uint32 hartid, uint32 irq_id);
extern void write_clint_msip_one(uint32 hartid);
extern void write_clint_msip_zero(uint32 hartid);

#endif
