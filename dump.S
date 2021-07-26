.global _start
_start:
	push  {r4, r5, r6, r7, r8, fp, lr}
#if 1
	adr r5, asd
	ldr r4, [r5]
	ldrh r3, [r4]
	add r4, #2
	str r4, [r5]
#endif
#if 0
	adr r5, asd
	ldr r3, [r5]
	add r3, #5
	str r3, [r5]
	mov r3, #0
	ldr r3, [r5]
#endif
	pop   {r4, r5, r6, r7, r8, fp, pc}

//asd: .long 0x40000000
asd: .int 10