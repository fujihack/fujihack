// Main init/start file
.global _start

// Global Offset Table data from linker
.extern _got_start
.extern _got_end

// No data before _start!
_start:
	push {r1, r2, r3, r4, r5, r6, lr}

	// Need to fix up GOT first. It has addresses starting from the
	// beginning of the file, not PC relative. This code fixes it.
	ldr r1, =_got_start
	ldr r2, =_got_end	

	sub r2, r1 // subtract, r2 == len

	// Skip if GOT is zero
	cmp r2, #0x0
	beq skip

	got_top:
		sub r2, #0x4
		adr r3, _start // get base addr
		add r3, r1 // add _got_end
		add r3, r2 // add curr len
		ldr r4, [r3] // get value

		adr r5, _start // get base addr
		add r4, r5 // get new addr
		str r4, [r3] // store new value
	cmp r2, #0x0
	bne got_top

	skip:
	adr r0, _start
	bl entry

	pop {r1, r2, r3, r4, r5, r6, pc}

// For debugging patches
#if 0
#undef FIRM_RST_CONFIG1
#undef FIRM_RST_CONFIG2
#undef FIRM_RST_WRITE
#define FIRM_RST_CONFIG1 0
#define FIRM_RST_CONFIG2 0
#define FIRM_RST_WRITE 0

.align 4
#include "../patch/debug.S"
.align 4
#endif
