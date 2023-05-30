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

/* Read from the machine HART id. */
extern uint32 read_mhartid(void);
/* Read from the current thread pointer. */
extern uint32 read_tp(void);
/* Write to the current thread pointer. */
extern void write_tp(uint32);
/* Read from machine interrupt enable. */
extern uint32 read_mie(void);
/* Write to machine interrupt enable. */
extern void write_mie(uint32);
/* Read from machine status register. */
extern uint32 read_mstatus(void);
/* Write to machine status register. */
extern void write_mstatus(uint32);
/* Read from machine scratch register. */
extern uint32 read_mscratch(void);
/* Write to machine scratch register. */
extern void write_mscratch(uint32);
/* Set PLIC priority of given interrupt source id. */
extern void plic_set_priority(uint32 irq_id, int pri_val);
/* Set hart specific PLIC machine enable of given interrupt source id. */
extern void plic_set_m_enable(uint32 hartid, uint32 irq_id);
/* Set PLIC machine threshold of given hart id. */
extern void plic_set_m_threshold(uint32 hartid, int thr_val);
/* Read from the PLIC machine claim which specifies current interrupt source id. */
extern int plic_m_claim(uint32 hartid);
/* Write back to PLIC machine complete to 
inform completion of external interrupt handling. */
extern void plic_m_complete(uint32 hartid, uint32 irq_id);
/* Set CLINT.MSIP bit to 1 to generate a software interruption. 
MSIP: machine mode software interrupt. */
extern void write_clint_msip_one(uint32 hartid);
/* Set CLINT.MSIP bit to 0 to inform software interruption handled. 
MSIP: machine mode software interrupt. */
extern void write_clint_msip_zero(uint32 hartid);

#endif
