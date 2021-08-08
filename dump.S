.global _start
_start:
	push  {r4, r5, r6, r7, r8, fp, lr}
	// To reference strings, dont use ldr.
	// Code seems to be PIC on most cameras.
	adr r4, mystring
	bl MEMCPY
	pop   {r4, r5, r6, r7, r8, fp, pc}

mystring: .string "Hello, World"