// Main code execution hacks - allows code to be loaded in via USB. See src/
// For XF-1 ONLY!

#ifndef CAN_DO_EXECUTER
	#error "This model doesn't seem to be able to run the executer!"
#endif

.global _start
_start:
	push  {r4, r5, r6, r7, r8, lr}

	// Hijack a useless PTP function (get thumbnail)
	// It latches onto it, without destroying the actual
	// function.

	ldr r4, =MEM_PTP_THUMBNAIL
	adr r6, hack
	mov r5, #35 // how many insts

	top:
		ldr r7, [r6]
		str r7, [r4]
		sub r4, #4
		sub r6, #4

		sub r5, #1
		cmp r5, #0
	bne top

	pop   {r4, r5, r6, r7, r8, pc}

// Where to copy the incoming code
temp_addr: .long MEM_FREE_SPACE
put_addr: .long MEM_FREE_SPACE
custom:
	// r0 is #0 when returning the header
	// #1 is used for the actual code
	cmp r0, #1
	bne nohack

	ldr r6, [r1, #0x10] // get first PTP parameter from r1
	ldr r5, [r1, #0x14] // get second parameter

	// Problems with sending zero to PTP,
	// command #8 will be used to write it
	cmp r6, #4
	bne h
	eor r5, r5, r5
	mov r5, #0
	mov r6, #5
	h:

	// #5 - write byte
	cmp r6, #5
	bne n1
		adr r9, put_addr
		ldr r8, [r9]
		strb r5, [r8]
		add r8, #1
		str r8, [r9]
	n1:

	// #6 - run code
	cmp r6, #6
	bne n2
		adr r9, temp_addr
		ldr r9, [r9]
		// blx r9
		// GCC whining about unsupported instructions
		.byte 0x39, 0xff, 0x2f, 0xe1
	n2:

	// #7 - reset address
	cmp r6, #7
	bne n3
		adr r8, put_addr
		adr r9, temp_addr
		ldr r9, [r9]
		str r9, [r8]
	n3:

	nohack:
	mov r6, r1
	b return

	.byte 0xf0, 0x4d, 0x2d, 0xe9 // raw instruction in the ptp function
	add r11, sp, #0x1c
	sub sp, sp, #0x1c
hack:
	b custom
return:
