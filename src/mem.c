#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "ff_io.h"

void *heap_end = NULL;

void sys_init_mem() {
	heap_end = (void *)MEM_UNUSED_SPACE + (1 * 1024 * 1024);
}

void *_sbrk(int incr) {
	void *prev = heap_end;
	heap_end += incr;
	return prev;
}
