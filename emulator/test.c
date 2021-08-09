__asm__(".global _start");

// Trampoline
unsigned long entry();
void _start() {
	entry();
}

// Jump to a function in Fujifilm code
void test();
__asm__(
	".global test\n"
	"test:\n"
	"b 0x001e1ca0\n" // Appears to be a substring function.
);

char *hello = "123456Hello World";

// Code booter
unsigned long entry() {
	test(hello, 0, 6);
	
	return hello;
}