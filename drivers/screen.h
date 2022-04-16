#ifndef DIMAOS_DRIVER_SCREEN_H
#define DIMAOS_DRIVER_SCREEN_H

#define VIDEO_BASE_MEMORY 0xb8000

#define VIDEO_MAX_ROW 25
#define VIDEO_MAX_COLUMN 80


#define VIDEO_BLACK 0x0
#define VIDEO_WHITE 0xf
#define VIDEO_ATTRIBUTE(BGCOLOR, FGCOLOR) ((BGCOLOR) << 4 | (FGCOLOR))
#define VIDEO_WHITE_ON_BLACK VIDEO_ATTRIBUTE(VIDEO_BLACK, VIDEO_WHITE)

#define VIDEO_OFFSET(row, column) 2 * ((column) + (row) * VIDEO_MAX_COLUMN)
#define VIDEO_OFFSET_ROW(offset) offset / (2 * VIDEO_MAX_COLUMN)
#define VIDEO_OFFSET_COLUMN(offset) (offset - (VIDEO_OFFSET_ROW(offset) * 2 * VIDEO_MAX_COLUMN)) / 2
#define VIDEO_ADDRESS(row, column) (VIDEO_BASE_MEMORY + VIDEO_OFFSET(row, column))
#define VIDEO_END_ADDRESS VIDEO_ADDRESS(VIDEO_MAX_ROW - 1, VIDEO_MAX_COLUMN - 1)	

#define VIDEO_SCREEN_CTRL 0x3D4
#define VIDEO_SCREEN_DATA 0x3D5

void print_at(char* message, unsigned int row, unsigned int col);
void print(char* message);
void clear_screen();

#endif