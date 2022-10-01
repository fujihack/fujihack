.global _dbg_patch
_dbg_patch:
	push {r1-r10, lr}

	// Initialize RST rendering configs
	// Not exactly necessary
	mov r0, #0xf
	bl FIRM_RST_CONFIG1
	mov r0, #0xa
	bl FIRM_RST_CONFIG2

	mov r5, #0x1 // r5 will hold curr line

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
	bl findFuncHeader
	cmp r0, #0x0
	beq i_quit

	// Store
	adr r1, search_ptp
	str r0, [r1]

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
	bl findFuncHeader
	cmp r0, #0x0
	beq i_quit

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

i_hijack:
	ldr r2, search_ptp
	adr r3, _ptp_9805_hack
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

// GCC -O4 was better at optimizing this
// uintptr_t bruteForceSearch(uint8_t *bytes, int length)
.global bruteForceSearch
bruteForceSearch:
	push    {r4, r5, r6, lr}
	mov     r5, r0
	ldrb    r6, [r0]
	rsb     lr, r0, #0
	add     r4, r0, r1
	mov     r0, #0
	s_L2:
	ldrb    r3, [r0]
	cmp     r3, r6
	bne     s_L5
	cmp     r0, r5
	beq     s_L5
	cmp     r1, #0
	popeq   {r4, r5, r6, pc}
	mov     r3, r5
	b       s_L6
	s_L4:
	cmp     r4, r3
	popeq   {r4, r5, r6, pc}
	s_L6:
	ldrb    ip, [r3, #1]!
	ldrb    r2, [lr, r3]
	cmp     ip, r2
	beq     s_L4
	s_L5:
	add     r0, r0, #1
	add     lr, lr, #1
	cmp     r0, #16777216
	bne     s_L2
	mov     r0, #0
	pop     {r4, r5, r6, pc}


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

#include "ptp.S"

.align 4
iteration: .int 0x0

// movw r2, #0xa808
.align 4
.global search_ptp
search_ptp: .byte 0x8, 0x28, 0xa, 0xe3

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
