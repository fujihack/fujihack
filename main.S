// XF-1 Tests ONLY!
.global _start
_start:
	push  {r4, r5, r6, r7, r8, lr}

	// Hijack a memcpy function

	ldr r4, =0x00e56fbc
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

temp_addr: .long 0x00e572e8
put_addr: .long 0x00e572e8 // custom test addr
custom:
	cmp r0, #1
	bne nohack
	ldr r6, [r1, #0x10]
	ldr r5, [r1, #0x14]

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

	.byte 0xf0, 0x4d, 0x2d, 0xe9
	add r11, sp, #0x1c
	sub sp, sp, #0x1c
hack:
	b custom
return:
