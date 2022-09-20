// 0x9805 Hijack
.global _ptp_hack
_ptp_hack:
	cmp r0, #0x0
	bne ptp_end:
	ldr r0, [r1, #(4 * 4)] // param 1
	ldr r0, [r1, #(4 * 4)] // param 2
	


	

	ptp_end:
	ptp_write_addr: .int 0x0
	ptp_temp_addr: .int 0x0
