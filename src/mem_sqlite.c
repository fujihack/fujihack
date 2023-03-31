// SQLite only has ~2mb allocatable RAM
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "io.h"
#include "sqlite.h"

void sys_init_mem() {
	struct sqlite3_mem_methods *m = (struct sqlite3_mem_methods *)SQLITE_MEM_METHODS;
	fuji_init_sqlite();
	while (m->xMalloc == 0) {
		fuji_task_sleep(1);
	}
}

void *malloc(size_t size) {
	struct sqlite3_mem_methods *m = (struct sqlite3_mem_methods *)SQLITE_MEM_METHODS;
	return m->xMalloc(size);
}

void *calloc(size_t nmemb, size_t size) {
	struct sqlite3_mem_methods *m = (struct sqlite3_mem_methods *)SQLITE_MEM_METHODS;
	void *ptr = malloc(nmemb * size);
	memset(ptr, 0, nmemb * size);
	return ptr;
}

void *realloc(void *ptr, size_t size) {
	struct sqlite3_mem_methods *m = (struct sqlite3_mem_methods *)SQLITE_MEM_METHODS;
	return m->xRealloc(ptr, size);
}

void free(void *ptr) {
	struct sqlite3_mem_methods *m = (struct sqlite3_mem_methods *)SQLITE_MEM_METHODS;
	if (ptr < 1000) { return; }
	m->xFree(ptr);
}

// Fix non WEAK functions
void * __wrap__malloc_r(struct _reent *a, size_t b) {
	return malloc(b);
}

int _sbrk_r() {
	errno = 1;
	return -1;
}
