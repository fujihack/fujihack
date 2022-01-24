#include <stdint.h>

// Entry trampoline for functions under
// start()
uintptr_t start();
void _start() {
	start();
	start();
}

void random_strcpy(char *b, char *i);

char buffer[100];

// Code booter
uintptr_t start() {
	char *buffer1 = "Hello, World";
	random_strcpy(buffer, buffer1);
	return (uintptr_t)buffer;
}

