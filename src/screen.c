#include <stdint.h>

#include "fujihack.h"
#include "fujifilm.h"

uint32_t screen_buffer = GET_SCREEN_LAYER(0);

void bmp_pixel(int x, int y, uint32_t rgb) {
	uint32_t *buf = (uint32_t *)((uintptr_t)screen_buffer);
	buf[SCREEN_WIDTH * y + x] = rgb;
}

void bmp_clear(uint32_t rgb) {
	uint32_t *buf = (uint32_t *)((uintptr_t)screen_buffer);
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
		buf[i] = rgb;
	}
}

int console_curr = 0;
void uart_str(char string[]) {
	fuji_screen_write(string, 1, 1 + console_curr, TEXT_BLACK, TEXT_WHITE);
	console_curr++;

	if (console_curr > 9) {
		console_curr = 0;
		fuji_discard_text_buffer();
	}
}
