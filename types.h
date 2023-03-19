#ifndef __TYPES_H__
#define __TYPES_H__

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

typedef uint32 regis;
// registers are 32bits width on rv32

typedef struct
{
    // all registers
    // called by its ABI name

    // ignore zero
    regis ra;  // x1, return address
    regis sp;  // x2, stack pointer
    regis gp;  // x3, global pointer
    regis tp;  // x4, thread pointer
    regis t0;  // x5, temporary/alternate link register
    regis t1;  // x6, temporary
    regis t2;  // x7
    regis s0;  // x8, saved register/frame pointer
    regis s1;  // x9, saved register
    regis a0;  // x10, function argument/return value
    regis a1;  // x11
    regis a2;  // x12, function argument
    regis a3;  // x13
    regis a4;  // x14
    regis a5;  // x15
    regis a6;  // x16
    regis a7;  // x17
    regis s2;  // x18, saved register
    regis s3;  // x19
    regis s4;  // x20
    regis s5;  // x21
    regis s6;  // x22
    regis s7;  // x23
    regis s8;  // x24
    regis s9;  // x25
    regis s10; // x26
    regis s11; // x27
    regis t3;  // x28, temporary
    regis t4;  // x29
    regis t5;  // x30
    regis t6;  // x31
    // ignore floating point registers
} Context;

#endif
