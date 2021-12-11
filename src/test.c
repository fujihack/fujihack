// This code is injected into the Fujifilm camera

#ifndef MODEL_NAME
	#include "../model/xf1.h"
#endif

#include <string.h>
#include "sqlite.h"

int dump_test();
char get_drive();
int fuji_fopen();

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

void entry() {
	char *model = (char *)MEM_MODEL_TEXT;
	sqlite_snprintf(0x20, model, "Test: 0x%x", ((unsigned int *)0x01628656)[0]);

	int *fudge = (int *)BUF;
	for (int i = 0; i < 1920*1080; i++) {
		fudge[i] = -1;
	}

	for (int x = 0; x < 100; x++) {
		for (int y = 50; y < 100; y++) {
			pixel(x, y);
		}
	}

	rect(50, 50, 100, 100);
}
