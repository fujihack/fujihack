// 0x9805 Hijack
.global _ptp_hack
_ptp_hack:
	push {r1, r2, r3, r4, pc}
	cmp r0, #0x1
	bne ptp_end
	ldr r0, [r1, #(0x10)] // param 1
	ldr r3, [r1, #(0x14)] // param 2

	// Problems with sending zero to PTP,
	// command #4 will be used to write it

	cmp r0, #0x4 // operation 4 is zero
	bne not_zero
		eor r4, r4, r4 // reset data to 0
		mov r0, #5 // set to write operation
	not_zero:

	// #5 write byte
	cmp r0, #0x5
	bne not_5
		adr r5, temp_addr
		ldr r6, [r5]
		strb r3, [r6] // store byte in mem
		add r6, #1
		str r6, [r5] // write counter
	not_5:

	// #6 - Run code
	cmp r0, #0x6
	bne not_6
		ldr r5, temp_addr
		blx r5 // expected to not modify r1
		b ptp_end // r0 may be modified
	not_6:

	// #7 - Reset addr
	cmp r0, #0x7
	bne not_7
		adr r5, temp_addr
		adr r6, perm_addr
		ldr r6, [r6]
		str r6, [r5]
	not_7:

	ptp_end:

	mov r0, r1 // param_struct
	mov r1, #0x2000 // return code
	add r1, #0x1
	mov r2, r1
	ldr r5, search_ptp_finish
	blx r5

	pop {r1, r2, r3, r4, lr}

temp_addr: .int 0x0
perm_addr: .int 0x0

.extern search_ptp
.extern search_ptp_finish

// An option for area in which to load code
_ptp_hack_end:
