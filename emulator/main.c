#include <stdint.h>

#include <sqlite.h>
#include <hijack.h>
#include <fujifilm.h>

char buffer[16];

uint32_t x = 0xdeadBEEF;

void *entry() {
	uint8_t *t = (uint8_t*)0x40000008;

	sqlite_snprintf(sizeof(buffer), buffer, "Hello %X", x);
	return buffer;
}

