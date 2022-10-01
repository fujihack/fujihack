// This code is ran in preview menu

#define MAX_SIZE 0x100000

.global _file_loader
_file_loader:
	push {r0, r1, r2, r3, r4, r5, r6, r7, r8, lr}

	// r8 = sqlite_malloc(MAX_SIZE)
	bl fuji_init_sqlite
	mov r0, #0x100000
	bl sqlite_malloc
	mov r8, r4

	// file[0] = fuji_drive();
	adr r1, file
	bl fuji_drive
	strb r0, [r1]

	// filep = fuji_fopen(FUJI_FOPEN_HANDLER, file, 1)
	bl fuji_toggle
	ldr r0, =FUJI_FOPEN_HANDLER
	adr r1, file
	mov r2, #0x1
	bl fuji_fopen
	adr r1, filep
	str r0, [r1]
	bl fuji_toggle

	bl fuji_zero

	// fread(FUJI_FREAD_HANDLER, filep, MAX_SIZE, r8)
	bl fuji_toggle
	ldr r0, =FUJI_FREAD_HANDLER
	adr r1, file
	mov r2, #MAX_SIZE // size
	mov r3, r8 // set to alloc'd addr
	bl fuji_fread
	bl fuji_toggle

	bl fuji_zero

	// fuji_fclose(FUJI_FCLOSE_HANDLER, filep, 0x0, 0x0)
	bl fuji_toggle
	ldr r0, =FUJI_FCLOSE_HANDLER
	adr r1, file
	mov r2, #0x0
	mov r3, #0x0
	bl fuji_fread
	bl fuji_toggle

	bl fuji_zero

	// fuji_screen_write(run_fujihack, 1, 1, 0, 7)
	adr r0, run_fujihack
	mov r1, #0x1
	mov r2, #0x1
	mov r3, #0x0
	mov r4, #0x7
	bl fuji_screen_write

	blx r8

	// fuji_screen_write(press_ok, 1, 2, 0, 7)
	adr r0, press_ok
	mov r1, #0x1
	mov r2, #0x2
	mov r3, #0x0
	mov r4, #0x7
	bl fuji_screen_write

	bl fuji_screen_clear

	exit:
	pop {r0, r1, r2, r3, r4, r5, r6, r7, r8, pc}
filep: .int 0x0
run_once: .byte 0x0
.align 4
file: .string "X:\\FH.BIN"
run_fujihack: .string "Run FujiHack.."
press_ok: .string "Press OK"
bxlr: bx lr
