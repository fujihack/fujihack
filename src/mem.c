#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "ff_io.h"

uint8_t *heap_end = NULL;

void sys_init_mem() {
	heap_end = (uint8_t *)MEM_UNUSED_SPACE + (1 * 1024 * 1024);
}

uint8_t *_sbrk(int incr) {
	uint8_t *prev = heap_end;
	heap_end += incr;
	return prev;
}
