#ifndef MODEL_NAME
	#include "../model/xf1.h"
#endif

#include <string.h>
#include "sqlite.h"

#define WIDTH 640
#define HEIGHT 480

#define BUF2 0x1cee77e + ((WIDTH * HEIGHT) * 0)

#define BUFFER 0x1ce8bee - (WIDTH * HEIGHT)

void pixel(int x, int y) {
	int *buf = (int *)BUFFER;
	
	buf[WIDTH * y + x] = 0x0;
}

void rect(int x1, int y1, int w1, int h1) {
	for (int x = x1; x < w1+x1; x++) {
		for (int y = y1; y < h1+y1; y++) {
			pixel(x, y);
		}
	}
}

void entry() {
	int *fudge = (int *)BUFFER;

	for (int i = 0; i < 640 * 480; i++) {
		fudge[i] = 0xffffffff;
	}

	rect(0, 0, 100, 100);
	rect(100, 100, 100, 100);
	rect(200, 200, 100, 100);
	rect(300, 300, 100, 100);
}
