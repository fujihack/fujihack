asm(".code 32");
asm(".global _start");

// Entry trampoline for functions under
// start()
unsigned long start();
void _start() {
	start();
}

// Jump to a function in Fujifilm code
unsigned int test();
__asm__(
	".global test\n"
	"test:\n"
	"b 0x001e16a0\n"
);

static struct C {
	char a[100];
	int b;
	int d;
	char c[50];
}c = {
	"Hello",
	'A', 'A',
	"Goodbye"
};

// Code booter
unsigned long start() {
	test(c.a, c.c);
	
	return c.a;
}