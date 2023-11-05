// Assembly generation functions - will be included in custom assembler
// Copyright (C) 2022-2023 Frontier by Daniel C - Apache License
#include <stdint.h>

void asm_gen_branch(void *base, void *to, void *buffer) {
	((uint32_t*)buffer)[0] = ((to - base - 8) >> 2) & 0x00ffffff; // 16mb limit
	((uint8_t*)buffer)[3] = 0xea;
}

void asm_gen_call(void *base, void *to, void *buffer) {
	asm_gen_branch(base, to, buffer);
	((uint8_t*)buffer)[3] = 0xeb;
}

void asm_gen_nop(void *buffer) {
	((uint32_t*)buffer)[0] = 0xe320f000; // NOP
}

void asm_gen_nops(void *buffer, int n) {
	for (int i = 0; i < n; i++) {
		asm_gen_nop(buffer + (n * 4));
	}
}	
