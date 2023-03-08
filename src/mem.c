#include <stddef.h>
#include <stdlib.h>
#include "fujifilm.h"
#include "sqlite.h"

void sys_mem_init() {
	fuji_init_sqlite();
}

void *malloc(size_t size) {
	return sqlite_mallocAlarm(size);
}

void *calloc(size_t size, size_t a) {
	return sqlite_mallocAlarm(size);
}

void *realloc(void *ptr, size_t size) {
	return sqlite_mallocAlarm(size);
}

void free(void *ptr) {
	
}

void * __wrap__malloc_r(struct _reent *a, size_t b) {
	return NULL;
}

void _free_r(struct _reent *a, void *b) _NOTHROW {
	
}

void _sbrk_r() {
	
}
