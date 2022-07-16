#include <stdint.h>
#include <string.h>

// ARM32 parasitic function hijack
// Overwrites the function's original code so we
// can put in our own. May crash. Be careful.

void overwrite_function(uint32_t *addr, uintptr_t newFunc) {
	char export[] = {
		0xfe, 0x41, 0x2d, 0xe9, // push {r1, r2, r3, r4, r5, r6, r7, r8, lr}
		0x8, 0x80, 0x8f, 0xe2,  // adr r8, x
		0x0, 0x80, 0x98, 0xe5,  // ldr r8, [r8]
		0x38, 0xff, 0x2f, 0xe1, // blx r8
		0xfe, 0x81, 0xbd, 0xe8, // pop {r1, r2, r3, r4, r5, r6, r7, r8, pc}
		// x:
	};
	memcpy(addr, export, sizeof(export));
	addr[sizeof(export) / 4] = newFunc;
}
