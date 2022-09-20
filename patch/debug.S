.global _start
_start:
	push {r0-r10, lr}

	// Initialize RST rendering configs
	mov r0, #0xf
	bl FIRM_RST_CONFIG1
	mov r0, 0xa
	bl FIRM_RST_CONFIG2

	// Setup iteration
	ldrb r0, =iteration
	cmp r1, #0x3
	be i_e
	cmp r0, #0x0
	be i_txt
	b i_i

	i_i:
	ldrb r1, =iteration
	add r1, #0x1
	adr r0, iteration
	strb r0, [r1]

	i_e:
	pop {r0-r10, pc}

i_txt:
	mov r0, #0x1
	mov r1, #0x2
	adr r2, fh_intro
	bl FIRM_RST_WRITE
b i_i

i_search:
	mov r0, 0x0 // start at 0x0
	s_top:
		ldr r1, [r0]
		ldr r2, =search_ptp
		cmp r1, r2
		bne s_i
		ldr r2, =(search_ptp + 0x4)
		cmp r2, r2
		bne s_i
		b s_match
	s_i:
	add r0, #0x4
	b s_top
b i_i

s_match:
	adr r2, buffer
	mov r0, #'Y'
	str r0, [r2, #0x0]
	

	mov r0, #0x1
	mov r1, #0x4	
	bl fuji_rst_write
b i_i

#include "alpha-int.S"

.align 4
iteration: .byte 0x0

.align 4
search_ptp: .byte 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0

.align 4
fh_intro: .string "FujiHack DBG"

.align 4
failed_search: .string "Search failed"

buffer:
