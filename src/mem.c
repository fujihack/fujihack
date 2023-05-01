#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "io.h"

void *heap_end = NULL;

void sys_init_mem() {
	heap_end = (void *)MEM_FLASH_DUMP + 0x100000;
}

void *_sbrk(int incr) {
	void *prev = heap_end;
	heap_end += incr;
	return prev;
}
