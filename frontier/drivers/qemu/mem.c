extern int _symbol_table_start;

void sys_init_mem() {}

void *heap_end = 0;
void *_sbrk(int incr) {
	if (heap_end == 0) {
		heap_end = (void *)(_symbol_table_start + 0x1000);
	}

	void *prev = heap_end;

	heap_end += incr;
	return prev;
}
