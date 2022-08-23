#ifndef HIJACK_H
#define HIJACK_H

#include <stdint.h>

#define PATCH32(addr, val) ((uint32_t*)addr)[0] = (uint32_t)val;

#define PATCH16(addr, val) ((uint16_t*)addr)[0] = (uint16_t)val;

#define PATCH8(addr, val) ((uint8_t*)addr)[0] = (uint8_t)val;

// write bx lr
#define KILLFUNC(addr) ((uint32_t*)addr)[0] = 0xe12fff1e;

// write b .
#define HALTFUNC(addr) ((uint32_t*)addr)[0] = 0xeafffffe;

// write bl 0
#define CRASHFUNC(addr) ((uint32_t*)addr)[0] = 0xebffbffe;

void generate_branch(uint32_t base, uint32_t to, uint8_t *buffer);
void generate_call(uint32_t base, uint32_t to, uint8_t *buffer);
void generate_nop(uint8_t *buffer);

#endif
