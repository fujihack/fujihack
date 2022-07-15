// Code to jump to MEM_DUMP_ADDR when the injection trigger
// function is too small for main.S

// Define stubs.h for a small message

.global _start
_start:
	push {r1, r2, r3, r4, r5, r6, r7, r8, lr}

	adr r4, addr
	ldr r4, [r4]
	bx r4

#ifndef NO_MESSAGE
	// Little mesage, this uses the standard ARM assembly "preprocessor"
	// To test if a symbol is defined
	.ifdef fuji_screen_write
		adr r0, message
		mov r1, #0x1
		mov r2, #0x1
		mov r3, #0x0
		mov r4, #0x7

		adr r5, fpic_fuji_screen_write
		ldr r5, [r5]
		bx r5
	.endif
#endif

	pop {r1, r2, r3, r4, r5, r6, r7, r8, pc}
	addr: .int MEM_DUMP_ADDR
#ifndef NO_MESSAGE
	.ifdef fuji_screen_write
		fpic_fuji_screen_write: .int fuji_screen_write
		message: .string "FujiHack"
	.endif
#endif
