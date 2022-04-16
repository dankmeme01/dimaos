#include "screen.h"
#include <kernel/low_level.h>
#include <kernel/memory.h>
#include <kernel/string.h>

// Private functions.
int get_cursor_offset();
void set_cursor_offset(int offset);
int print_char(char c, int row, int col, char attribute);

int print_char(char c, int row, int col, char attribute) {
	unsigned char* videomem = (unsigned char*)VIDEO_BASE_MEMORY;

	if (!attribute) {
		attribute = VIDEO_WHITE_ON_BLACK;
	}
	
	if (col >= VIDEO_MAX_COLUMN || row >= VIDEO_MAX_ROW) {
		videomem[2 * (VIDEO_MAX_COLUMN) * (VIDEO_MAX_ROW)-2] = 'E';
		videomem[2 * (VIDEO_MAX_COLUMN) * (VIDEO_MAX_ROW)-1] = VIDEO_WHITE_ON_BLACK;
		return VIDEO_OFFSET(row, col);
	}
	
		
	int offset;
	if (col >= 0 && row >= 0) {
		offset = VIDEO_OFFSET(row, col);
	}
	else {
		offset = get_cursor_offset();
	}

	if (c == '\n') {
		row = VIDEO_OFFSET_ROW(offset);
		offset = VIDEO_OFFSET(row + 1, 0);
	}
	else {
		videomem[offset] = c;
		videomem[offset + 1] = attribute;
		offset += 2;
	}

	if (offset >= VIDEO_MAX_COLUMN * VIDEO_MAX_ROW * 2) {
		for (int i = 1; i < VIDEO_MAX_ROW; i++) {
			memcpy((void*)VIDEO_ADDRESS(i, 0), (void*)VIDEO_ADDRESS(i - 1, 0), VIDEO_MAX_COLUMN * 2);
		}
			
		char* lastline = (char*)VIDEO_ADDRESS(VIDEO_MAX_ROW - 1, 0);
		for (int i = 0; i < VIDEO_MAX_COLUMN * 2; i++)
			lastline[i] = 0;

		offset -= 2 * VIDEO_MAX_COLUMN;	
	}

	set_cursor_offset(offset);

	return offset;
}

int get_cursor_offset() {
	port_byte_out(VIDEO_SCREEN_CTRL, 14);
	int offset = port_byte_in(VIDEO_SCREEN_DATA) << 8;
	port_byte_out(VIDEO_SCREEN_CTRL, 15);
	offset += port_byte_in(VIDEO_SCREEN_DATA);
	return offset * 2;
}

void set_cursor_offset(int offset) {
	offset /= 2;
	port_byte_out(VIDEO_SCREEN_CTRL, 14);
	port_byte_out(VIDEO_SCREEN_DATA, (unsigned char)(offset >> 8));
	port_byte_out(VIDEO_SCREEN_CTRL, 15);
	port_byte_out(VIDEO_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void print_at(char* message, unsigned int row, unsigned int col) {
	int offset;
	if (col >= 0 && row >= 0) {
		offset = VIDEO_OFFSET(row, col);
	}
	else {		
		offset = get_cursor_offset();
		row = VIDEO_OFFSET_ROW(offset);
		col = VIDEO_OFFSET_COLUMN(offset);
	}

	int i = 0;
	while (message[i] != 0) {
		offset = print_char(message[i++], row, col, VIDEO_WHITE_ON_BLACK);
		row = VIDEO_OFFSET_ROW(offset);
		col = VIDEO_OFFSET_COLUMN(offset);
	}
}

void print(char* message) {
	print_at(message, -1, -1);
}

void clear_screen() {
	char* videomem = (char*)VIDEO_BASE_MEMORY;
	for (int i = 0; i < VIDEO_MAX_ROW * VIDEO_MAX_COLUMN; i++) {
		videomem[i * 2] = ' ';;
		videomem[i * 2 + 1] = VIDEO_WHITE_ON_BLACK;
	}
	set_cursor_offset(VIDEO_OFFSET(0, 0));
}