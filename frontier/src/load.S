// Generic ARM32 starter script
.extern _start

.global sys_entry
sys_entry:

.extern _got_start
.extern _got_end

// Need to fix up GOT first. It has addresses starting from the
// beginning of the file, not PC relative. This code fixes it.
ldr r1, =_got_start
ldr r2, =_got_end

sub r2, r1 // subtract, r2 == len

// Skip if GOT is zero
cmp r2, #0x0
beq skip

got_top:
	sub r2, #0x4
	ldr r3, =_start_dat // get base addr
	add r3, r1 // add _got_end
	add r3, r2 // add curr len
	ldr r4, [r3] // get value

	ldr r5, =_start_dat // get base addr
	add r4, r5 // get new addr
	str r4, [r3] // store new value
cmp r2, #0x0
bne got_top

skip:

// Quick code to clear BSS
mov   r0,#0               // get a zero
ldr   r1,=_bss_start      // -> bss start
ldr   r2,=_bss_end        // -> bss end
2: cmp   r1,r2            // check if data to clear
strlo r0,[r1],#4          // clear 4 bytes
blo   2b                  // loop until don

.extern entry
adr lr, after
b entry
after:
bl exit
b .

_start_dat: .int _start
