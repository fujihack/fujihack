// This code is injected into the Fujifilm camera

#ifndef MODEL_NAME
	#include "../model/xf1.h"
#endif

#include <string.h>
#include "sqlite.h"

int dump_test();
char get_drive();
int fuji_fopen();

// screen buffer testing
#define BUF_3 0x1cef200 - 0x82 - (640 * 4)
#define BUF_2 0x1cee77e + ((648 * 480) * -1) + 50 - 3 + 1800 - 22

#define BUF 0x1cee77e + ((648 * 480) * -1)

#define WIDTH 640

void pixel(int x, int y) {
	int *buf = (int *)BUF;
	buf[WIDTH * y + 1 + x] = 0x0;
}

void rect(int x1, int y1, int w1, int h1) {
	for (int x = x1; x < w1+x1; x++) {
		for (int y = y1; y < h1+y1; y++) {
			pixel(x, y);
		}
	}
}

void entry() {
	char *model = (char *)MEM_MODEL_TEXT;
	sqlite_snprintf(0x20, model, "Test: 0x%x", ((unsigned int *)0x01628656)[0]); // 0x28b00d8

	int *fudge = (int *)BUF;

	for (int i = 0; i < 640 * 480; i++) {
		fudge[i] = 0xffffffff;
	}

	rect(0, 50, 100, 100);
	rect(0, 200, 100, 100);
	rect(300, 300, 100, 100);
}
