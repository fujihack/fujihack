.global _start
_start:
	push  {r4, r5, r6, r7, r8, fp, lr}

	add   fp, sp, #0x18
	sub   sp, sp, #0x14

	mov   r4, r0
	mov   r6, r1
	sub   r5, fp, #0x2c

// str r5 into param
mov r0, #'A'
strb r0, [r5]

	mov   r3, #0
	strh  r3, [fp, #-0x20]
	mov   r3, #3
	strh  r3, [fp, #-0x1e]

	mov   r0, r6
	mov   r1, r5
	mov   r2, #0x10
	bl    0x0050abcc // 

	add   r0, r6, r0
	mov   r1, #2
	ldrb  r2, [r4]
	bl    0x00516c48

	mov   r7, r0
	ldr   r3, [r4, #4]
	cmp   r3, #0
	moveq r0, r0
	moveq r5, #0x16
	beq   l2

	mov   r0, r7
	mov   r1, #3
	mov   r2, #0
	bl    0x00516c48

	mov   r5, #0x1c
l2:
	movw  r1, #0x101
	ldrb  r2, [r4, #0x4c]
	bl    0x00516c48

	mov   r8, r0
	add   r5, r5, #6
	ldr   r3, [r4, #4]
	cmp   r3, #0
	beq   l1
	rsb   r6, r6, r0
	sub   r1, fp, #0x18
	str   r6, [r1, #-4]!

	add   r0, r7, #2
	mov   r2, #4
	bl    0x0050abcc

	mov   r0, r8
	add   r1, r4, #4
	mov   r2, #0x48
	bl    0x0050abcc

	add   r5, r5, #0x48
l1:
	mov   r0, r5
	sub   sp, fp, #0x18
	pop   {r4, r5, r6, r7, r8, fp, pc}