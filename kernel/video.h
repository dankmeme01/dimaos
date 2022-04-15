#ifndef DIMAOS_VGA_H
#define DIMAOS_VGA_H

#define WHITE_ON_BLACK 0x0f

void vga_putchar(char c, unsigned int row, unsigned int column, unsigned char properties);

void vga_putchars(char* chars, unsigned int row, unsigned int column, unsigned char properties);

#endif