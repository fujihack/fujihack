#ifdef STUB_H
#error "stub.h included twice. Catastrophic error."
#endif

#ifndef STUB_H
#define STUB_H

#ifdef FPIC
	// Define a trampoline, instead of relying on the
	// compiler to generate exactly what I want.
	#define NSTUB(name, addr) \
		.global name; \
		.extern name; \
		.func; \
		name:; \
			adr r9, name##_addr; \
			ldr r9, [r9]; \
			bx r9; \
			name##_addr: .int (addr); \
		.endfunc;
#else
	// Define a plain ELF symbol
	#define NSTUB(name, addr) \
		.global name; \
		.extern name; \
		name = (addr)
#endif

#endif
