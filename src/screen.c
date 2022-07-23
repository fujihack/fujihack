#include "fujihack.h"
#include "fujifilm.h"

void disp_pixel(int x, int y) {
	uint32_t *buf = (uint32_t *)SCREEN_BUFFER;
	buf[SCREEN_WIDTH * y + x] = 0xcccccccc;
}

void disp_clear() {
	uint32_t *buf = (uint32_t *)SCREEN_BUFFER;
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
		buf[i] = 0x00000000;
	}
}

void disp_rect(int x1, int y1, int w1, int h1) {
	for (int x = x1; x < w1+x1; x++) {
		for (int y = y1; y < h1+y1; y++) {
			disp_pixel(x, y);
		}
	}
}

// Testing 3x3 font stuff
#ifdef INCLUDE_FONT_STUFF
void font_draw_pixel(int x, int y) {
	disp_pixel(x, y);
}

#include "font/font.h"
#include "font/lib.c"
#endif
