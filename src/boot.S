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

	// Quick code to clear BSS
	mov   r0,#0                     // get a zero
	ldr   r1,=_bss_start           // -> bss start
	ldr   r2,=_bss_end           // -> bss end
	2: cmp   r1,r2                     // check if data to clear
	strlo r0,[r1],#4                // clear 4 bytes
	blo   2b                        // loop until done
		
	adr r0, _start
	bl entry

	pop {r1, r2, r3, r4, r5, r6, pc}
