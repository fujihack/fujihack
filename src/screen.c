#include "fujihack.h"
#include "fujifilm.h"

#define LAYER 3

void disp_pixel(int x, int y, int col) {
	uint32_t *buf = (uint32_t *)GET_SCREEN_LAYER(LAYER);
	buf[SCREEN_WIDTH * y + x] = col;
}

void disp_clear(int col) {
	uint32_t *buf = (uint32_t *)GET_SCREEN_LAYER(LAYER);
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
		buf[i] = col;
	}
}

void disp_rect(int x1, int y1, int w1, int h1, int col) {
	for (int x = x1; x < w1+x1; x++) {
		for (int y = y1; y < h1+y1; y++) {
			disp_pixel(x, y, col);
		}
	}
}

// Testing read, alloc, in font binary
#ifdef STANDALONE_FONT_TEST
int font_print_char(struct Font *f, int x, int y, char c) {
	// Loop to "null terminator character"
	int match = 0;
	for (int l = 0; f[l].letter != 0; l++) {
		if (f[l].letter == c) {
			match = l;
			break;
		}
	}

	// Loop through 7 high 5 wide monochrome font
	int maxLength = 0;
	for (int py = 0; py < 7; py++) {
		for (int px = 0; px < 5; px++) {
			if (f[match].code[py][px] == '#') {
				disp_pixel(x, y, 0xffffffff);

				// Dynamix width character spacing
				if (px > maxLength) {
					maxLength = px;
				}
			}
		}
	}

	return maxLength;
}

void testfont() {
	fuji_init_sqlite();
	struct Font *font = (struct Font*)sqlite_malloc(3276);

	char file[] = "X:\\font.bin";
	file[0] = fuji_drive();
	FILE *fp = fopen(file, 0);
	fread(font, 3276, 1, fp);
	fclose(fp);

	font_print_char(font, 10, 10, 'A');
}
#endif

// Testing 3x3 font stuff
#ifdef INCLUDE_FONT_STUFF
void font_draw_pixel(int x, int y) {
	disp_pixel(x, y);
}

#include "font/font.h"
#include "font/lib.c"
#endif
