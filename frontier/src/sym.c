// Copyright (C) 2022-2023 Frontier by Daniel C - Apache License
// Global runtime symbol mananger. Next time I should use a linked list
// rather than an array of variable length buffers.
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sys.h>

extern uint32_t _symbol_table_start;

#pragma pack(push, 1)

// A variable length structure containing information for a single symbol
struct TblEntry {
	uint32_t addr;
	uint16_t length;
	uint8_t type;
	uint8_t etc;
	char string[];
};

#define DEFAULT_TABLE_SIZE 10000
#define MAX_TABLES 10

// Each table points to raw memory containing a series of TblEntry structures. Each TblEntry is variable length.
// For each table, the 'length' attribute is for how many bytes the buffer is. This is done primarily because it's
// how the symbols for the OS image is stored (as a binary file appended to the OS image)
int current_table_index = 0;
struct GlobalSyms {
	uintptr_t table;
	int length;
}global_syms[MAX_TABLES];

#pragma pack(pop)

// Gets the current length of all the symbols added to a specific table
int get_table_length(int i) {
	void *tmp = (void *)(global_syms[i].table);

	int of = 0;
	while (1) {
		struct TblEntry *x = (struct TblEntry *)(tmp + of);
		if (x->addr == 0) return of;
		of += 8 + x->length;
	}
}

int allocate_new_table() {
	current_table_index++;
	global_syms[current_table_index].table = (uintptr_t)malloc(DEFAULT_TABLE_SIZE);
	global_syms[current_table_index].length = DEFAULT_TABLE_SIZE;
	memset((void *)global_syms[current_table_index].table, 0, DEFAULT_TABLE_SIZE);

	if (global_syms[current_table_index].table == NULL) {
		sys_debug("SYM: Fatal - out of memory\n");
		while (1);
	}

	return 0;
}

int sym_new(char *name, uint32_t value) {
	int length = get_table_length(current_table_index);

	// Allocate a new table if necessary
	int predicted_size = length + (int)strlen(name) + (int)sizeof(struct TblEntry);

	if (predicted_size >= global_syms[current_table_index].length || global_syms[current_table_index].length == 0) {
		allocate_new_table();
	}

	length = get_table_length(current_table_index);
	struct TblEntry *x = (struct TblEntry *)(global_syms[current_table_index].table + length);
	x->addr = value;
	x->length = strlen(name);
	memcpy(x->string, name, x->length);

	return 0;
}

int sys_init_syms() {
	global_syms[0].table = ((uintptr_t)(&_symbol_table_start));
	global_syms[0].length = 0;
	allocate_new_table();

	sys_debug("Initialized internal symbols\n");
	sys_debug("Table length: %d\n", get_table_length(0));
	
	return 0;
}

void *sym(const char *name) {
	for (int i = 0; i < current_table_index + 1; i++) {
		int of = 0;
		uintptr_t table = global_syms[i].table;
		while (1) {
			struct TblEntry *x = (struct TblEntry *)(table + of);
			if (x->addr == 0) break;
			if (!strncmp(name, x->string, x->length)) {
				return (void *)((uintptr_t)x->addr);
			} else {
				of += 8 + x->length;
			}
		}
	}

	return NULL;
}
