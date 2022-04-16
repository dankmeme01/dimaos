#include "idt.h"

void set_idt_gate(int n, u32 handler)
{
	idt[n].offset_low = LOW16(handler);
	idt[n].selector = KERNEL_CS;
	idt[n].zero = 0;
	idt[n].flags = 0x8E;
	idt[n].offset_high = HIGH16(handler);
}

void set_idt() {
	idt_reg.base = (u32)&idt;
	idt_reg.limit = IDT_ENTRIES * sizeof(idt_entry_t) - 1;
	__asm__ __volatile__("lidtl (%0)" : : "r" (&idt_reg));
}