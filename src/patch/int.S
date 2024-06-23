// Converts int to str codes in only ~100 bytes,
// see etc/ab-int.c

#define INT_C1 'A'
#define INT_C2 'Z'

// intToBuffer(int x, void *buf)
.global intToBuffer
intToBuffer:
	push {r0-r6, lr}
	mov r6, r1
	adr r1, temp_int
	str r0, [r1]

	mov r4, #0x0 // curr byte
	mov r5, #0x0 // buffer byte

	sib_top_1:
		ldrb r0, [r1, r4] // curr byte
		mov r2, #INT_C1 // a
		mov r3, #INT_C1 // b
		sib_top:
			cmp r0, #0x0 // is byte finished?
			beq sib_end
			cmp r3, #INT_C2 // end of b?
			bne sib_1
			add r2, #0x1 // decrement a
			mov r3, #INT_C1 // reset b
			sib_1:
			add r3, #0x1
			sub r0, #0x1 // dec main value
		b sib_top
		sib_end:
		strb r2, [r6, r5]
		add r5, #0x1
		strb r3, [r6, r5]
		add r5, #0x1

		add r4, #0x1 // inc byte
		cmp r4, #0x3 // is curr byte over 4?
		ble sib_top_1
	mov r2, #0x0 // null terminator
	//sub r5, #0x2
	strb r2, [r6, r5]
	pop {r0-r6, pc}

temp_int: .int 0x0
