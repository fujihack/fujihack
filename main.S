// Main code execution hacks - allows code to be loaded in via USB, see src/
// Tested: XF-1

// This copies a part of itself above the get_thumb PTP function, allowing
// a basic RAM copying interface between over USB. It hijacks the function
// header, jumps to the code above, and then returns back, hoping that
// it preserved everything correctly for the original code.

#ifndef CAN_DO_EXECUTER
	#error "This model doesn't seem to be able to run the executer!"
#endif

// This section is copied into the firmware on compile time,
// preferably by the PrintIM hack.
.global _start
_start:
	push {r4, r5, r6, r7, r8, lr}

	// The "top" loop carefully copies instructions starting from
	// "hack" up to the top of this file into the PTP code. That means
	// it will probably copy in extra instructions, but I don't care.

	ldr r4, =MEM_PTP_THUMBNAIL
	adr r6, hack
	mov r5, #35 // how many insts to copy

	top:
		ldr r7, [r6]
		str r7, [r4]
		sub r4, #4
		sub r6, #4

		sub r5, #1
		cmp r5, #0
	bne top

	pop {r4, r5, r6, r7, r8, pc}

// Everything from here on out is code
// that will be copied into a PTP function
// The bottom part hijacks the target function
// header, and the custom code overwrites a
// some other PTP function (doesn't seem to crash though)
temp_addr: .long MEM_FREE_SPACE // Used for incrementing
put_addr: .long MEM_FREE_SPACE // unchanged, copied into put_addr
custom:
	// r0 is #0 when returning the PTP header
 	// #1 is used for the actual PTP command
	cmp r0, #1
	bne nohack

	ldr r6, [r1, #0x10] // get first PTP parameter from r1
	ldr r5, [r1, #0x14] // get second parameter

	// Problems with sending zero to PTP,
	// command #4 will be used to write it
	cmp r6, #4
	bne h
		eor r5, r5, r5 // reset register
		mov r5, #0 // reset register again for some reason
		mov r6, #5 // set action to #5, write byte
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
		blx r9
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

	// Copy in exact function, but replace the "mov r6, r1"
	// with a jump to above 
	push {r4, r5, r6, r7, r8, sl, fp, lr}
	add r11, sp, #0x1c
	sub sp, sp, #0x1c
hack:
	b custom
return:
