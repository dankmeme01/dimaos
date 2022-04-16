#ifndef DIMAOS_CPU_IDT_H
#define DIMAOS_CPU_IDT_H

#include "types.h"

#define KERNEL_CS 0x08	// kernel code segment

typedef struct {
	u16 offset_low;
	u16 selector;
	u8 zero;
	u8 flags;
	u16 offset_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
	u16 limit;
	u32 base;
} __attribute__((packed)) idt_ptr_t;

#define IDT_ENTRIES 256
idt_entry_t idt[IDT_ENTRIES];
idt_ptr_t idt_reg;

void set_idt_gate(int n, u32 handler);
void set_idt();

#endif