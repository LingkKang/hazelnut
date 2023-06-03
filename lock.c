#include "defs.h"

void init_lock(SpinLock *lock)
{
    lock->locked = 0;
}

void acquire_lock(SpinLock *lock)
{
    while (__sync_lock_test_and_set(&lock->locked, 1) != 0)
        ;
}

void release_lock(SpinLock *lock)
{
    __sync_lock_release(&lock->locked);
    return;
}
