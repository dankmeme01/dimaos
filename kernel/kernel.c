#include <drivers/screen.h>
#include <kernel/string.h>
#include <kernel/memory.h>
#include <cpu/isr.h>
#include <cpu/idt.h>

void fill_amogus();

void main() {
	clear_screen();
	isr_install();
	print("Lmao");
	__asm__ __volatile__("int $23");
	__asm__ __volatile__("int $24");
}

void fill_amogus() {
	for (int i = 0; i < 5; i++) {
		print("BIG AMOGUS!");
	}

	char* amogus_chunk = (char*)malloc(sizeof(char) * 220);
	for (int i = 0; i < 20; i++) {
		amogus_chunk[i * 11] = 'B';
		amogus_chunk[i * 11 + 1] = 'I';
		amogus_chunk[i * 11 + 2] = 'G';
		amogus_chunk[i * 11 + 3] = ' ';
		amogus_chunk[i * 11 + 4] = 'A';
		amogus_chunk[i * 11 + 5] = 'M';
		amogus_chunk[i * 11 + 6] = 'O';
		amogus_chunk[i * 11 + 7] = 'G';
		amogus_chunk[i * 11 + 8] = 'U';
		amogus_chunk[i * 11 + 9] = 'S';
		amogus_chunk[i * 11 + 10] = '!';
	}

	for (int i = 0; i < 0xffffffff; i += 6) {
		// fill the memory with amogus
		memcpy((void*)amogus_chunk, (void*)i, sizeof(char) * 220);
		print_at("Currently writing to: ", 0, 0);
		print_at(int_to_str(i), 1, 0);
	}
}