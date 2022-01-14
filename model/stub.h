// Inspired by Magic Lantern
#define NSTUB(name, addr) \
	.global name; \
	.type name, %function; \
	.extern name; \
	name = (addr)
