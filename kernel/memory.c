#include "memory.h"

struct Chunk _available = { .begin = (void*)MEM_START, .size = 0xffffffff - MEM_START };

struct ChunkData _taken_chunks[0xffff];
int _taken_chunks_size = 0;

void* malloc(unsigned int size) {
	if (size == 0) {
		return NULL;
	}
	
	for (int i = 0; i < _taken_chunks_size; i++) {
		if (!_taken_chunks[i].available || _taken_chunks[i].chunk.begin == NULL) {
			continue;
		}
		
		if (_taken_chunks[i].chunk.size == size) {
			_taken_chunks[i].available = false;
			return _taken_chunks[i].chunk.begin;
		}
	}

	if (size > _available.size) {
		return NULL;
	}
	void* result = _available.begin;
	_available.begin += size;
	_available.size -= size;
	
	struct Chunk c;
	c.begin = result;
	c.size = size;

	struct ChunkData cd;
	cd.chunk = c;
	cd.available = false;

	_taken_chunks[_taken_chunks_size++] = cd;
	return result;
}

void free(void* memory) {
	for (int i = 0; i < _taken_chunks_size; i++) {
		if (_taken_chunks[i].chunk.begin == memory) {
			_taken_chunks[i].available = true;
			return;
		}
	}
}

void zero_memory(void* memory, unsigned int size) {
	for (int i = 0; i < size; i++) {
		((char*)memory)[i] = 0;
	}
}

void memcpy(void* from, void* to, unsigned int size) {
	unsigned char* ucfrom = (unsigned char*)from;
	unsigned char* ucto = (unsigned char*)to;
	for (int i = 0; i < size; i++) {
		*(ucto + i) = *(ucfrom + i);
	}
}