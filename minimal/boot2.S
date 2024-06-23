.global _start
_start:
	push {r0, r1, r2, lr}

	dsb
	isb sy

	// Flush instruction cache
	mov r0, pc
    mov r0, r0, LSL #4
    mcr p15, 0, r0, c7, c5, 1

	dsb
	isb sy

	bl entry

	mov r0, #0x1
	pop {r0, r1, r2, pc}
	bx lr
