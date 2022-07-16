.global _start

_start:
	push {r1, r2, r3, r4, r5, r6, lr}
	adr r0, _start
	bl entry

	pop {r1, r2, r3, r4, r5, r6, pc}
