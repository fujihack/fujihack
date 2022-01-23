asm(".code 32");
asm(".arm");
asm(".global _start");

// Entry trampoline for functions under
// start()
unsigned long start();
void _start() {
	start();
	((char *)0x2101168)[0] = 'Z';
}

// Test a function in firmware
unsigned int test();
__asm__(".global test\ntest:\n"
		"b 0x0072f90c\n");

char buffer[10];

// Code booter
unsigned long start() {
	test(buffer, "asd");
	return buffer;
}

