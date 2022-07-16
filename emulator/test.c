#include <stdint.h>

#include <sqlite.h>
#include <fujifilm.h>

char buffer[100];

char *_start() {
	char str[] = "@@@@@@@@@@";
	return parse_check(str, str + 6, 0, (char**)&str);
}

#include <lib.c>
