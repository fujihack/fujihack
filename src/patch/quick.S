// Quicker/smaller version of FujiHack DBG
.global _quick_ptp
_quick_ptp:
	push {r1-r10, fp, lr}

	mov r0, #0xf
	bl FIRM_RST_CONFIG1
	mov r0, #0xd
	bl FIRM_RST_CONFIG2

	// Change permanent address for code loading (after this file)
	// This must be done before everything is copied
	adr r1, _quick_ptp_end
	adr r2, perm_addr
	str r1, [r2]

	ldr r1, search_ptp
	adr r2, _ptp_9805_hack
	mov r3, #0x0
	ctop:
		ldr r4, [r2, r3]
		str r4, [r1, r3]
		add r3, #0x4
		cmp r3, #(65 * 4)
		bne ctop

	mov r0, #0x1
	mov r1, #0x1
	adr r2, hacked
	bl FIRM_RST_WRITE

	mov r0, #0x0
	pop {r1-r10, fp, lr}

.align 4
hacked: .string "Fuji Hacked"

#define PTP_ABSOLUTE
.align 4
#include "ptp.S"

.align 4
search_ptp: .int MEM_PTP_9805

.align 4
search_ptp_finish: .int MEM_PTP_RETURN

_quick_ptp_end:
