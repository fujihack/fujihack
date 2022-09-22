.global _start_
_start_:
	push {r1-r10, lr}

	mov r5, #0x0 // r5 will hold curr line

	// Initialize RST rendering configs
	// Not exactly necessary
	mov r0, #0xf
	bl FIRM_RST_CONFIG1
	mov r0, #0xa
	bl FIRM_RST_CONFIG2

	// Switch curr iteration
	ldr r0, iteration
	cmp r0, #0x0
	beq i_txt
	cmp r0, #0x1
	beq i_search
	cmp r0, #0x2
	beq i_hijack
	cmp r0, #0x3
	beq i_end
	b i_increment

	i_increment:
	ldr r1, iteration
	add r1, #0x1
	adr r0, iteration
	str r1, [r0]

	i_end:
	pop {r1-r10, pc}

i_txt:
	adr r0, fh_intro
	bl printRst
b i_increment

i_search:
	// Find
	adr r0, search_ptp
	mov r1, #0x4
	bl bruteForceSearch
	bl findFuncHeader
	cmp r0, #0x0
	beq i_quit

	// Store
	adr r1, search_ptp
	str r0, [r1]

	// Print
	adr r1, buffer
	bl intToBuffer
	adr r0, buffer
	bl printRst

	// Find
	adr r0, search_ptp_finish
	mov r1, #0x4
	bl bruteForceSearch
	bl findFuncHeader
	cmp r0, #0x0
	beq i_quit

	// Store
	adr r1, search_ptp_finish
	str r0, [r1]

	// Print
	adr r1, buffer
	bl intToBuffer
	adr r0, buffer
	bl printRst
b i_increment

i_hijack:
	ldr r2, search_ptp
	adr r3, _ptp_hack
	mov r1, #0x0
	i_h:
		ldr r4, [r3, r1]
		str r4, [r2, r1]
		add r1, #0x4
		cmp r1, #(40 * 4) // about 40 instructions (?)
		bne i_h
	// Store permanent address for code loading (after PTP code)
	adr r1, _ptp_hack_end
	adr r2, perm_addr
	str r1, [r2]

	adr r0, success
	bl printRst
b i_quit

i_quit:
	adr r1, iteration
	mov r2, #0x3
	str r2, [r1]
	b i_end

// uintptr_t bruteForceSearch(uint8_t *bytes, int length)
bruteForceSearch:
	mov r2, r0
	movs r0, #0
	push {r4, lr}
		.L2:
		movs r3, #0
		b .L5
		.L4:
		cmp r3, #3
		beq .L1
		adds r3, #1
		.L5:
		ldrb r4, [r2, r3]
		ldrb r1, [r3, r0]
		cmp r4, r1
		beq .L4
		adds r0, #1
		cmp r0, #0xf0000000
		bne .L2
		movs r0, #0
		.L1:
	pop {r4, pc}

// findFuncHeader(uint32_t addr)
findFuncHeader:
	push {r1, lr}
		ffh:
		sub r0, r0, #0x4
		ldrb r1, [r0, #0x2]
		cmp r1, #0x2d
		bne ffh
	pop {r1, pc}

printRst:
	push {r1, r2, lr}
		mov r2, r0
		mov r0, #0x1
		mov r1, r5
		bl FIRM_RST_WRITE
		add r5, #0x2 // increment double line
	pop {r1, r2, pc}

#include "int.S"

#include "ptp.S"

.align 4
iteration: .int 0x0

// movw r2, #0xa808
.align 4
search_ptp: .byte 0x8, 0x28, 0x0a, 0xe3

// add r2, r3, #0x7000
.align 4
search_ptp_finish: .byte 0x7, 0x2a, 0x83, 0xe2

.align 4
fh_intro: .string "FujiHack DBG"

.align 4
failed_search: .string "Search fail"

.align 4
success: .string "Hacked"

.align 4
buffer:
