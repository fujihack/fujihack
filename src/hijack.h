// Arm32 function hijacker

#define u32 unsigned int


/*

push {r11, lr}

XX push {r11, lr}
mov r0, #123
pop {r11, pc}


*/
__asm__(".global ");

void hijack(u32 *addr, u32 new) {
	
}
