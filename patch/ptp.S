// 0x9805 Hijack
.extern search_ptp
.extern search_ptp_finish

#define PTP_CMD_ZERO 0x4
#define PTP_CMD_WRITE 0x5
#define PTP_CMD_RUN 0x6
#define PTP_CMD_RESET 0x7
#define PTP_CMD_SETADDR 0x8
#define PTP_CMD_GET 0x9

.global _ptp_9805_hack
_ptp_9805_hack:
	push {r1-r10, lr}
	cmp r0, #0x1
	bne ptp_end

	ldr r0, [r1, #(0x10)] // param 1
	ldr r3, [r1, #(0x14)] // param 2

	// Set first param to zero
	adr r5, pk_param1
	mov r6, #0x0
	str r6, [r5]

	// PTP parameters can't be zero, a custom cmd
	// must be made to send zeros

	cmp r0, #PTP_CMD_ZERO // operation 4 is zero
	bne not_zero
		mov r3, #0x0 // set to zero
		mov r0, #5 // set to write operation
	not_zero:

	// #5 write byte
	cmp r0, #PTP_CMD_WRITE
	bne not_5
		adr r5, temp_addr
		ldr r6, [r5]
		strb r3, [r6] // store byte in mem
		add r6, #1
		str r6, [r5] // write counter
	not_5:

	// #6 - Run code
	cmp r0, #PTP_CMD_RUN
	bne not_6
		ldr r5, perm_addr
		blx r5 // expected to not modify r1
		b ptp_end // r0 may be modified
	not_6:

	// #7 - Reset addr
	cmp r0, #PTP_CMD_RESET
	bne not_7
		adr r5, temp_addr
		ldr r6, perm_addr
		str r6, [r5]
	not_7:

	// #8 - Set addr
	cmp r0, #PTP_CMD_SETADDR
	bne not_8
		adr r6, perm_addr
		str r3, [r6]
	not_8:

	// #9 - Get 32 bit
	cmp r0, #PTP_CMD_GET
	bne not_9
		ldr r5, [r3] // get uint32_t at param r3
		adr r6, pk_param1
		str r5, [r6]
	not_9:

	ptp_end:
	mov r0, #0x2000 // OK return code
	add r0, #0x1
	override_ret_code:
	adr r1, pk_code
	str r0, [r1]

	adr r0, return_packet
	mov r1, #0x0
	ldr r5, search_ptp_finish
	blx r5

	pop {r1-r10, pc}

.global perm_addr
temp_addr: .int 0x0
perm_addr: .int 0x0

return_packet:
pk_code: .int 0x2001
pk_transid: .int 0x0 // zero is fine
pk_sessionid: .int 0x0 // same here
pk_nparams: .int 0x1
pk_param1: .int 0x0

// An option for area in which to load code
_ptp_hack_end:
