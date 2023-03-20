#include "defs.h"

#define MAX_TASKS 10
#define MAX_TASK 10
#define STACK_SIZE 1024

uint8 task_stacks[MAX_TASKS][STACK_SIZE];
Context tasks[MAX_TASKS];
Context os_context;
Context *current_context;

int _num_of_tasks = 0;

int task_create(void *routine_entry)
{
    // return 0 - success
    // return -1 - fail

    if (_num_of_tasks < MAX_TASKS)
    {
        tasks[_num_of_tasks].sp = (regis)&task_stacks[_num_of_tasks][STACK_SIZE - 1];
        tasks[_num_of_tasks].ra = (regis)routine_entry;
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
    Context *old_context = current_context;
    current_context = &os_context;
    // switch context
    switch_context(old_context, current_context);
}
