// Define FPIC when you define STUBS if position
// independent code is needed

#ifdef FPIC
	// Define a trampoline, instead of relying on the
	// compiler to generate exactly what I want.
	#define NSTUB(name, addr) \
		.global name; \
		.extern name; \
		name:; \
			adr r9, name##_addr; \
			ldr r9, [r9]; \
			bx r9; \
			name##_addr: .int (addr);
#else
	// Define a plain ELF symbol
	#define NSTUB(name, addr) \
		.global name; \
		.extern name; \
		name = (addr)
#endif
