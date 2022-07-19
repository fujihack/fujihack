#ifndef MODEL_NAME
	#include "../model/xf1_101.h"
#endif

#include <string.h>
#include <stdint.h>
#include "fujihack.h"
#include "fujifilm.h"
#include "sqlite.h"

void pixel(int x, int y) {
	int *buf = (int *)SCREEN_BUFFER;
	buf[SCREEN_WIDTH * y + x] = 0xffffffff;
}

void rect(int x1, int y1, int w1, int h1) {
	for (int x = x1; x < w1+x1; x++) {
		for (int y = y1; y < h1+y1; y++) {
			pixel(x, y);
		}
	}
}

#define DUMP_SIZE_MB 256
#define DUMP_SIZE DUMP_SIZE_MB * 1000 * 1000

int bg_x = 0;
void memory_dump(char file[], uintptr_t location) {
	char buffer[16];
	sqlite_snprintf(16, buffer, "Dumping %uMB RAM", DUMP_SIZE_MB);
	fuji_screen_write(buffer, 1, 1, bg_x, 7);
	fuji_screen_write("Will lock up", 1, 2, 0, 7);

	uint8_t *mem = (uint8_t*)location;

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
	bg_x++;
}

#include "parasite.h"

void entry(uint32_t base) {
#if 0
	fujihack_init();
#endif
#if 0
	char *x = (char*)MEM_MODEL_TEXT;
	sqlite_snprintf(16, x, "Hello World");
#endif
#if 0
	memory_dump("X:\\RAM.BIN", 0x00000000);
#endif
}
