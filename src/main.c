#ifndef MODEL_NAME
	#include "../model/xf1.h"
#endif

#include <string.h>
#include <stdint.h>
#include "fujifilm.h"
#include "sqlite.h"

#if 0
#include "font/font.h"

void pixel(int x, int y) {
	int *buf = (int *)SCREEN_BUFFER;
	buf[SCREEN_WIDTH * y + x] = 0x0;
}

void rect(int x1, int y1, int w1, int h1) {
	for (int x = x1; x < w1+x1; x++) {
		for (int y = y1; y < h1+y1; y++) {
			pixel(x, y);
		}
	}
}

int printChar(int x, int y, char c) {
	// Loop to "null terminator character"
	int match = 0;
	for (int l = 0; font[l].letter != 0; l++) {
		if (font[l].letter == c) {
			match = l;
			break;
		}
	}

	// Loop through 7 high 5 wide monochrome font
	int maxLength = 0;
	for (int py = 0; py < 7; py++) {
		for (int px = 0; px < 5; px++) {
			if (font[match].code[py][px] == '#') {
				pixel(x + px, y + py);

				// Dynamix width character spacing
				if (px > maxLength) {
					maxLength = px;
				}
			}
		}
	}

	return maxLength;
}
#endif

#if 1

// 512 meg
#define DUMP_SIZE_MB 256
#define DUMP_SIZE DUMP_SIZE_MB * 1000 * 1000

void memory_dump() {
	char buffer[16];
	sqlite_snprintf(16, buffer, "Dumping %uMB RAM", DUMP_SIZE_MB);
	fuji_screen_write(buffer, 1, 1, 0, 7);
	fuji_screen_write("Will lock up", 1, 2, 0, 7);

	uint8_t *mem = (uint8_t*)0x0;

	char file[] = "X:\\RAM.BIN";
	file[0] = fuji_drive();

	fuji_toggle();
	void *fp = fuji_fopen(FUJI_FOPEN_HANDLER, file);
	fuji_toggle();
	fuji_zero();

	fuji_toggle();
	fuji_fwrite(FUJI_FWRITE_HANDLER, fp, DUMP_SIZE, mem);
	fuji_toggle();
	fuji_zero();

	fuji_toggle();
	fuji_fclose(FUJI_FCLOSE_HANDLER, fp, 0, (char*)0);
	fuji_toggle();
	fuji_zero();

	fuji_screen_write("Done.", 1, 3, 0, 7);
}
#endif

void entry() {
// Basic Test
#if 0
	char *x = (char*)MEM_MODEL_TEXT;
	sqlite_snprintf(16, x, "Hello World");
#endif
#if 0
	memory_dump();
#endif
}
