#include <stdint.h>

#include "fujihack.h"
#include "fujifilm.h"
#include "rst.h"

uintptr_t screen_buffer;
int sys_bmp_init() {
	// Write some permanent text so that a new layer is always present
	fuji_screen_write("new layer", 1, 1, TEXT_WHITE, TEXT_BLACK);

	fuji_task_sleep(100);

	uintptr_t *x = (uintptr_t *)(MEM_OPENGL_BUFFERS);
	screen_buffer = x[1];
}

int bmp_apply() {
	
}

void bmp_pixel(int x, int y, uint32_t rgb) {
	uint32_t *buf = (uint32_t *)((uintptr_t)screen_buffer);
	buf[SCREEN_WIDTH * y + x] = rgb | 0xff;
}

void bmp_clear(uint32_t rgb) {
	uint32_t *buf = (uint32_t *)((uintptr_t)screen_buffer);
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
		buf[i] = rgb;
	}
}
