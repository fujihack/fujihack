#include <stdint.h>

#include <sqlite.h>
#include <fujifilm.h>

void *main();
void *_start() {
	return main();
}

char buffer[12];

void *main() {
	sqlite_snprintf(sizeof(buffer), buffer, "Hello");
	return buffer;
}

#include <lib.c>
