#include "defs.h"

void acquire_lock(SpinLock *lock)
{
    while (__sync_lock_test_and_set(&lock->locked, 1) != 0)
        ;
}
