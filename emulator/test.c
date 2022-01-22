asm(".code 32");
asm(".arm");
asm(".global _start");

#include <sqlite.h>
#include <string.h>

char buffer[10];

void foo();

void _start() {
	foo();
}

void foo() {
	//astrcpy(buffer, "Hello");
}
