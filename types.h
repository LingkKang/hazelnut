#ifndef __TYPES_H__
#define __TYPES_H__

#include "memlayout.h"

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

typedef uint32 regis;
// registers are 32bits width on rv32

// Wrap all needed registers for context switching
typedef struct context
{
    // all registers
    // called by its ABI name

    // ignore zero
    regis ra;  // x1, return address, 0
    regis sp;  // x2, stack pointer
    regis gp;  // x3, global pointer
    regis tp;  // x4, thread pointer
    regis t0;  // x5, temporary/alternate link register, 16
    regis t1;  // x6, temporary
    regis t2;  // x7
    regis s0;  // x8, saved register/frame pointer
    regis s1;  // x9, saved register, 32
    regis a0;  // x10, function argument/return value
    regis a1;  // x11
    regis a2;  // x12, function argument
    regis a3;  // x13, 48
    regis a4;  // x14
    regis a5;  // x15
    regis a6;  // x16
    regis a7;  // x17, 64
    regis s2;  // x18, saved register
    regis s3;  // x19
    regis s4;  // x20
    regis s5;  // x21, 80
    regis s6;  // x22
    regis s7;  // x23
    regis s8;  // x24
    regis s9;  // x25, 96
    regis s10; // x26
    regis s11; // x27
    regis t3;  // x28, temporary
    regis t4;  // x29, 112
    regis t5;  // x30
    regis t6;  // x31
    regis pc;  // program counter, 124
    // ignore floating point registers
} Context;

// Simple spin lock for thread safety
typedef struct spinlock
{
    uint8 locked; // set to 1 for locked; 0 as unlocked
} SpinLock;

#endif
