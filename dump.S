// hs20exr
.global _start
_start:
	push  {r4, r5, r6, r7, r8, lr}

	// Hijack a memcpy function

	ldr r4, =0x0072fe14
	adr r6, hack
	mov r5, #25 // how many insts

	top:
		ldr r7, [r6]
		str r7, [r4]
		sub r4, #4
		sub r6, #4

		sub r5, #1
		cmp r5, #0
		bne top

	pop   {r4, r5, r6, r7, r8, pc}

	// The hack, everything here is copied into
	// another function

	a: .long 0x00e5e237 - 5 // where the output string is
	b: .long 0x800000 // start addr (approx)
	hijack:
		adr r4, a
		ldr r4, [r4]

		// Syncing mechanism. Slower, but
		// dont want to loose any bytes
		ldrb r5, [r4]
		add r5, #1
		cmp r5, #127
		bne as
			mov r5, #1

			// Update addr into output and
			// increment one
			adr r6, b
			ldr r6, [r6]

			// Load in 8 bytes
			ldr r7, [r6]
			str r7, [r4, #2]
			ldr r7, [r6, #4]
			str r7, [r4, #2 + 4]

			// increment 1 and store back
			add r6, #8
			adr r7, b
			str r6, [r7]
		as:
		strb r5, [r4]

		invalid:
		mov  r4, r1
	b resume
	
	push {r4, r5, r6, r7, fp}
	add  fp, sp, #0x10
	mov  ip, r0
hack:
	b hijack
resume:
