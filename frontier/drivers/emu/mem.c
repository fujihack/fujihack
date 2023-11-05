// Minimal backend code for libgcc memory manager
#include <stdint.h>
#include <string.h>

#include "emu.h"

void sys_init_mem() {}

void *heap_end = 0;
void *_sbrk(int incr) {
	if (heap_end == 0) {
		heap_end = (void *)(((uintptr_t *)MEM_ALLOC_START)[0]);
	}

	void *prev = heap_end;

	heap_end += incr;
	return prev;
}
