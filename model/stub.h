// Inspired by Magic Lantern
#ifndef STUB_H
#define STUB_H

#define NSTUB(name, addr) \
	.global name; \
	.type name, %function; \
	.extern name; \
	name = (addr)

#endif
