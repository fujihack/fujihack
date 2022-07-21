#ifndef HIJACK_H
#define HIJACK_H

#include <stdint.h>

void generate_branch(uint32_t base, uint32_t to, uint8_t *buffer);
void generate_call(uint32_t base, uint32_t to, uint8_t *buffer);

#endif
