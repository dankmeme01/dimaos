#ifndef DIMAOS_MEMORY_H
#define DIMAOS_MEMORY_H

#define MEM_START 0x00100000

#define NULL 0
#define bool int
#define true 1
#define false 0

struct Chunk {
	void* begin;
	unsigned int size;
};

struct ChunkData {
	struct Chunk chunk;
	bool available;
};

void* malloc(unsigned int size);
void free(void* memory);
void zero_memory(void* memory, unsigned int size);
void memcpy(void* from, void* to, unsigned int size);

#endif