#ifndef DIMAOS_CPU_TYPES_H
#define DIMAOS_CPU_TYPES_H

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef int i32;
typedef short i16;
typedef char i8;

// get lower and higher 16 bits of a 32 bit integer
#define LOW16(x) (u16)((x) & 0xFFFF)
#define HIGH16(x) (u16)(((x) >> 16) & 0xFFFF)

#endif