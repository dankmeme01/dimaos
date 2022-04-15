#!/bin/bash

export PATH="/usr/local/i386elfgcc/bin/:$PATH"

cd src
# Build the bootloader
nasm ./boot/boot.asm -f bin -o ../out/boot.bin

# make directories for all kernel modules
mkdir ../out/lib/video/ 2> /dev/null

# Build all the kernel modules
i386-elf-gcc -ffreestanding -c ./kernel/video/vga.c -o ../out/lib/video/vga.o # -std=gnu99 -Wall -Wextra -O2 -m32

# Build the kernel itself
i386-elf-gcc -ffreestanding -c ./kernel/kernel.c -o ../out/kernel.o -I./kernel # -std=gnu99 -O2 -Wall -Wextra

cd ../out

i386-elf-ld -Ttext 0x1000 -n --oformat binary ./kernel.o ./lib/video/vga.o -o ./kernel.bin

rm ../dimaos.bin 2> /dev/null

cat boot.bin kernel.bin > ../dimaos.bin

cd ..