#include "defs.h"

#define MAX_TASKS 10
#define STACK_SIZE 1024

uint8 task_stacks[MAX_TASKS][STACK_SIZE];
Context tasks[MAX_TASKS];
Context os_context;
Context *current_context;

int _num_of_tasks = 0;
int _current_task = -1;

void sched_init(void)
{
    // initialize `mscratch` to 0
    write_mscratch(0);

    // enable machine mode software interrupts
    write_mie(read_mie() | MIE_MSIE);
}

int task_create(void *routine_entry)
{
    // return 0 - success
    // return -1 - fail

    if (_num_of_tasks < MAX_TASKS)
    {
        tasks[_num_of_tasks].sp = (regis)&task_stacks[_num_of_tasks][STACK_SIZE - 1];
        tasks[_num_of_tasks].pc = (regis)routine_entry;
        _num_of_tasks++;
        return 0;
    }
    return -1;
}

void task_proceed(int i)
{
    // give control to tasks from OS
    current_context = &tasks[i];
    switch_context(&os_context, current_context);
}

void task_pause(void)
{
    // return control to OS
    kprintf("Switching ...\n");
    // save current context
    Context *old_context = current_context;
    // update current context with OS context
    current_context = &os_context;
    // switch context
    switch_context(old_context, current_context);
}

void task_yield(void)
{
    uint32 id = read_mhartid();
    // write clint.msip to 1
    write_clint_msip_one(id);
    return;
}

void task_scheduler(int proceed)
{
    if (_num_of_tasks <= 0)
    {
        panic("No task is running yet!");
        return;
    }
    _current_task = (_current_task + 1) % _num_of_tasks;
    Context *next = &(tasks[_current_task]);
    if (proceed)
    {
        switch_to(next);
    }
    else
    {
        start_task(next);
    }
}
