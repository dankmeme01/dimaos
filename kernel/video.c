#include "video.h"

char* VGA_BASE_MEMORY = (char*)0xb8000;

#define VGA_MAX_ROW 25
#define VGA_MAX_COLUMN 80

#define VGA_OFFSET(row, column) ((column) + (row) * 80)
#define VGA_ADDRESS(row, column) (VGA_BASE_MEMORY + 2 * VGA_OFFSET(row, column))

#define WHITE_ON_BLACK 0x0f

void vga_putchar(char c, unsigned int row, unsigned int column, unsigned char properties) {
	char* video_memory = VGA_ADDRESS(row, column);
	*video_memory = c;
	*(video_memory + 1) = properties;
}

void vga_putchars(char* chars, unsigned int row, unsigned int column, unsigned char properties) {
	char* video_memory = VGA_ADDRESS(row, column);
	while (*chars) {
		*video_memory = *chars;
		if (properties != 0) {
			*(video_memory + 1) = properties;
		}
		video_memory += 2;
		chars++;
	}
}