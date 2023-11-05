.cpu cortex-m0
.thumb

.extern main

.thumb_func
.global _start
_start:

stacktop: .word 0x20004000

.word reset
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang
.word hang

.thumb_func
reset:
	; jump to 32 bit ARM
    adr r0, main
    add r0, #0x1
    blx r0

.thumb_func
hang:   b .

.end
