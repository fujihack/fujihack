// Code to jump to MEM_DUMP_ADDR when the injection trigger
// function is too small for main.S

.global _start
_start:
	push {r1, r2, r3, r4, r5, r6, r7, r8, lr}

	adr r4, addr
	ldr r4, [r4]
	bx r4

	pop {r1, r2, r3, r4, r5, r6, r7, r8, pc}
	addr: .int MEM_DUMP_ADDR
