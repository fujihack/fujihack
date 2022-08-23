#include <stdint.h>

#include <sqlite.h>
#include <hijack.h>
#include <fujifilm.h>

void *main();
void *reloc(uint32_t base);

void *_start();
__asm__(
	".global _start\n"
	".extern main\n"
	"_start:\n"
	"adr r0, _start\n"
	"b reloc\n"
);

extern uint32_t _got_start[];
extern uint32_t _got_end[];

// Correct GOT offsets
void* reloc(uint32_t base) {
	uint32_t got_start = _got_start;
	uint32_t got_end = _got_end;

	int32_t len = (got_end - got_start) / 4 - 1;
	for (int i = 0; i < len; i++) {
		((uint32_t*)((uint32_t)got_start + (uint32_t)base))[i] += base;
	}

	return main();
}

#include <lib.c>

char buffer[12];

uint32_t test = 0x1234;

void *main() {
	sqlite_snprintf(sizeof(buffer), buffer, "Hello %x", test);
	return buffer;
}
