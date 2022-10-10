// This is a debugger program that is applied into
// the show_photo_properties function (most cameras 2009-2017)
// Since this function is 4k long, we aren't as restricted on
// code size.

.global _dbg_patch
_dbg_patch:
	push {r1-r10, fp, lr}

	// Initialize rasterizer rendering configs
	// Not exactly necessary
	// Might be able to tweak to be transparent, or different colors
	mov r0, #0xf
	bl FIRM_RST_CONFIG1
	mov r0, #0xd
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
	pop {r1-r10, fp, pc}

i_txt:
	mov r0, #0x1
	mov r1, #0x1
	adr r2, fh_intro
	bl FIRM_RST_WRITE
b i_increment

i_search:
	// Find
	adr r0, search_ptp
	mov r1, #0x4
	bl bruteForceSearch
	cmp r0, #0x0 // check err
	beq i_search_err
	bl findFuncHeader

	// Store
	adr r1, search_ptp
	str r0, [r1]

	// Print
	adr r1, buffer
	bl intToBuffer
	mov r0, #0x1
	mov r1, #0x1
	adr r2, buffer
	bl FIRM_RST_WRITE

	// Find
	adr r0, search_ptp_finish
	mov r1, #0x4
	bl bruteForceSearch
	cmp r0, #0x0
	beq i_search_err
	bl findFuncHeader

	// Store
	adr r1, search_ptp_finish
	str r0, [r1]

	// Print
	adr r1, buffer
	bl intToBuffer

	mov r0, #0x1
	mov r1, #0x3
	adr r2, buffer
	bl FIRM_RST_WRITE
b i_increment

i_search_err:
	mov r0, #0x1
	mov r1, #0x4
	adr r2, search_err
	bl FIRM_RST_WRITE
b i_quit

i_hijack:
	// Store permanent address for code loading (after this file)
	// This must be done before everything is copied
	adr r1, _dbg_patch_end
	adr r2, perm_addr
	str r1, [r2]

	ldr r2, search_ptp
	adr r3, _ptp_9805_hack
	mov r1, #0x0
	i_h:
		ldr r4, [r3, r1]
		str r4, [r2, r1]
		add r1, #0x4
		cmp r1, #(65 * 4) // about 65 instructions, plus the data under the code
		bne i_h

	mov r0, #0x1
	mov r1, #0x1
	adr r2, success
	bl FIRM_RST_WRITE
b i_quit

i_quit:
	adr r1, iteration
	mov r2, #0x3
	str r2, [r1]
	b i_end

// GCC -O4 was better at optimizing this, this is from Godbolt
// uintptr_t bruteForceSearch(uint8_t *bytes, int length)
.global bruteForceSearch
bruteForceSearch:
	push    {r4, r5, lr}
	mov     r5, r0
	sub     r4, r1, #1
	rsb     lr, r0, #0
	add     r4, r5, r4
	mov     r0, #0
	.L6:
	cmp     r0, r5
	beq     .L2
	ldrb    r2, [r5]        @ zero_extendqisi2
	ldrb    r3, [r0]        @ zero_extendqisi2
	cmp     r2, r3
	bne     .L2
	cmp     r1, #1
	popeq   {r4, r5, pc}
	mov     r3, r5
	b       .L4
	.L5:
	cmp     r3, r4
	popeq   {r4, r5, pc}
	.L4:
	ldrb    ip, [r3, #1]!   @ zero_extendqisi2
	ldrb    r2, [r3, lr]    @ zero_extendqisi2
	cmp     ip, r2
	beq     .L5
	.L2:
	add     r0, r0, #1
	cmp     r0, #0x02000000
	add     lr, lr, #1
	bne     .L6
	mov     r0, #0
	pop     {r4, r5, pc}

// uintptr_t findFuncHeader(uintptr_t addr)
.global findFuncHeader
findFuncHeader:
	push {r1, lr}
		ffh:
		sub r0, r0, #0x4
		ldrb r1, [r0, #0x2]
		cmp r1, #0x2d
		bne ffh
	pop {r1, pc}

#include "int.S"

// ptp.S will access search_ptp and search_ptp_finish
// locally, so that data must follow below to be copied
#define PTP_ABSOLUTE
#include "ptp.S"

// movw r2, #0xa808
.align 4
.global search_ptp
search_ptp: .byte 0x8, 0x28, 0xa, 0xe3

// add r2, r3, #0x7000
.align 4
search_ptp_finish: .byte 0x7, 0x2a, 0x83, 0xe2

.align 4
iteration: .int 0x0

.align 4
fh_intro: .string "FujiHack DBG"

.align 4
search_err: .string "Search fail"

.align 4
success: .string "Hacked"

// After here is both used as code and string buffer,
// after it is used as code, it should not be used as buffer anymore
.align 4
buffer:
_dbg_patch_end:
