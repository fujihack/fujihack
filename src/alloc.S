.global _start
// testing crap
_start:
	push {r0, r1, r2, r3, r4, r5, r6, lr}

	ldr r1, =0x00e56f34

	mov r0, #0x100
	bl 0x013fddcc
	str r0, [r1]

	pop {r0, r1, r2, r3, r4, r5, r6, pc}
