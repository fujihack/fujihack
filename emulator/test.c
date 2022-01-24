#include <stdint.h>

// Entry trampoline for functions under
// start()
char *main();
char *_start() {
	return main();
}

void random_strcpy(char *b, char *i);

char buffer[100];

// Code booter
char *main() {
	random_strcpy(buffer, "hey");
	return buffer;
}
