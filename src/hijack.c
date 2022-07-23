#include <stdint.h>

void generate_branch(uintptr_t base, uintptr_t to, uint8_t *buffer) {
	((uint32_t*)buffer)[0] = ((to - base - 8) >> 2) & 0x00ffffff;
	buffer[3] = 0xea;
}

void generate_call(uintptr_t base, uintptr_t to, uint8_t *buffer) {
	generate_branch(base, to, buffer);
	buffer[3] = 0xeb;
}

void generate_nop(uint8_t *buffer) {
	((uint32_t*)buffer)[0] = 0xe320f000; // NOP
}
