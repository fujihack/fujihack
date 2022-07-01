// Code to jump to MEM_DUMP_ADDR when injection trigger
// function is too small for main.S

.global _start
_start:
	push {r4, r5, r6, lr}

	adr r9, addr
	ldr r9, [r9]
	bx r9

	pop {r4, r5, r6, pc}
	addr: .int MEM_DUMP_ADDR
