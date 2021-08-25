asm(".code 32");
asm(".arm");
asm(".global _start");

// Entry trampoline for functions under
// start()
unsigned long start();
void _start() {
	start();
}

#define VERIFY_PTP_STRING_CODE 0x0037b444
int ptp_verify_string_code(unsigned short x);

unsigned int test();
__asm__(".global test\ntest:\n"
		"b 0x0037b444\n");

// Code booter
unsigned long start() {
	unsigned int b = test(0xb802);
	
	return b;
}