C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)

BUILDDIR = ./build
SOURCEDIR = .

OBJ = ${C_SOURCES:.c=.o}

all: dimaos.bin

run: all
	bochs.exe -q

dimaos.bin: boot/boot.bin build/kernel.bin
	cat $^ > $@

build/kernel.bin: kernel/kernel_entry.o ${OBJ}
	/usr/local/i386elfgcc/bin/i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

%.o : %.c ${HEADERS}
	/usr/local/i386elfgcc/bin/i386-elf-gcc -ffreestanding -c $< -o $@ -I./kernel/ -I./ -std=c11

%.o : %.asm
	nasm $< -f elf -o $@

%.bin : %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o dimaos.bin
	rm -rf kernel/*.o boot/*.bin drivers/*.o