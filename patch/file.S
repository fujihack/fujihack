// Patch to load executable binary from AUTO_ACT.SCR - requires RAM stubs
// This is designed to be executed in the INSTAX selection menu

.global _start
_start:
	push {r1, r2, r3, r4, r5, r6, r7, r8, sb, sl, fp, lr}

	mov r0, #0xf
	bl FIRM_RST_CONFIG1
	mov r0, #0xf
	bl FIRM_RST_CONFIG2

	ldr r9, _fuji_file_reset
	ldr r7, _fuji_file_wait

	blx r7 // fuji_file_wait()

	adr r0, handler
	adr r1, filename
	mov r2, #0x0 // read mode
	ldr r8, _fuji_fopen
	blx r8 // fuji_fopen()
	mov r6, r0 // store fd in r6
	blx r7 // fuji_file_wait()

	blx r9 // fuji_file_reset()


	ldrb r8, err_code // load addr buffer
	cmp r8, #0x0 // is err clear?
	bne err


	blx r7 // fuji_file_wait()

	adr r0, handler
	mov r1, r6 // fd
	mov r2, #0xffffffff // read -1 bytes (?)
	ldr r3, temp_buf
	ldr r8, _fuji_fread
	blx r8 // fuji_fread()

	blx r7 // fuji_file_wait()
	blx r9 // fuji_file_reset()	


	blx r7 // fuji_file_wait()

	adr r0, handler
	mov r1, r6 // fd
	ldr r8, _fuji_fclose
	blx r8 // fuji_fclose()

	blx r7 // fuji_file_wait()
	blx r9 // fuji_file_reset()

	// call read contents
	ldr r3, temp_buf
	blx r3

	// Default success message
	adr r2, message
	b quit

	// Err message
	err:
	adr r2, err_msg

	// Always print text when quit
	quit:
	mov r0, #0x3
	mov r1, #0x3
	bl FIRM_RST_WRITE
	
	mov r0, #0x0
	pop {r1, r2, r3, r4, r5, r6, r7, r8, sb, sl, fp, pc}

// Handler to store IO result in temp buffer
handler:
	push {r1, lr}

	adr r1, err_code
	strb r0, [r1]

	ldr r1, _fuji_file_reset
	blx r1
	
	pop {r1, pc}

// Pull the constants from header file stubs
_fuji_file_wait: .int fuji_file_wait
_fuji_file_reset: .int fuji_file_reset
_fuji_fopen: .int fuji_fopen
_fuji_fread: .int fuji_fread
_fuji_fclose: .int fuji_fclose

temp_buf: .int MEM_UNUSED_SPACE

// Doesn't need to be aligned
err_code: .byte 0x0
filename: .string "C:\\DCAA\\AUTO_ACT.SCR"
message: .string "Fujihacked!"
err_msg: .string "File Err!"
