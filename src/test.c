// This code is injected into the Fujifilm camera

#ifndef MODEL_NAME
	#include "../model/xf1.h"
#endif

#include <string.h>
#include "hijack.h"
#include "sqlite.h"

#if 0
#define BUF 0x1cef200 - 0x20

void pixel(int x, int y) {
	int *buf = (int *)BUF;
	buf[640 * y + x] = 0;
}

void rect(int x, int y, int w, int h) {
	for (; x < w; x++) {
		for (; y < h; y++) {
			pixel(x, y);
		}
	}
}

void writeUni(char *s, char *d) {
	while (*s) {
		*d = *s;
		s++;
		d += 2;
	}

	*d = 0;
}
#endif

void temp(int a, int b, int c) {
	char *model = (char *)MEM_MODEL_TEXT;
	sqlite_snprintf(0x20, model, "Test: %u, %u, %u", a, b, c);
}

int dump_test();
char get_drive();


#define FUJI_FILE_ERR 2
#define FUJI_FILE_EXIST 1
int fuji_fopen();
void fuji_fread();


void entry() {
	int a = fuji_fopen(&temp, "C:\\ASD", 0);

	fuji_fread(&temp, a, 10, 0x43e6ff0);

	char *model = (char *)MEM_MODEL_TEXT;
	sqlite_snprintf(0x20, model, "Test: %d", dump_test());
}
