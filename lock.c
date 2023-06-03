#include "defs.h"

/*
Initialize a spin lock.
*/
void init_lock(SpinLock *lock)
{
    lock->locked = 0;
}

/*
Acquire a spin lock atomically.
Check and lock the spinlock in one instruction if applicable.
*/
void acquire_lock(SpinLock *lock)
{
    while (__sync_lock_test_and_set(&lock->locked, 1) != 0)
        ;
}

/*
Release the spin lock.
*/
void release_lock(SpinLock *lock)
{
    __sync_lock_release(&lock->locked);
    return;
}
