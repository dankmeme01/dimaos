#include <video.h>

void main() {
	vga_putchar('S', 0, 0, WHITE_ON_BLACK);
	vga_putchars("Kernel successfully loaded! Hello from C :)", 1, 0, WHITE_ON_BLACK);
}