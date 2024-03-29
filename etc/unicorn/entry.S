// Main init file
.global _start

.extern _got_start
.extern _got_end

_start:
	push {r1, r2, r3, r4, r5, r6, lr}

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
