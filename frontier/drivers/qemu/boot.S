// ARM interrupt vector table
b _start
b .
b .
b .
b .

.global _start
_start:
ldr sp, =stack_top
bl entry
b .
