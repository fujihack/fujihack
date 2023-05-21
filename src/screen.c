#include <stdint.h>

#include "io.h"
#include "rst.h"

uintptr_t screen_buffer;
int sys_init_bmp() {
	struct RstText *rst = (struct RstText *)MEM_TEXT_LAYERS;
	rst->length = 1;

	// Write some permanent text so that a new layer is always present
	fuji_screen_write("new layer", 1, 1, 0, 7);

	fuji_task_sleep(100);

	uintptr_t *x = (uintptr_t *)(MEM_OPENGL_BUFFERS);
	screen_buffer = x[0];
}

int bmp_apply() {
	fuji_task_sleep(1);
}

void bmp_pixel(int x, int y, uint32_t rgb) {
	uint32_t *buf = (uint32_t *)((uintptr_t)screen_buffer);
	buf[SCREEN_WIDTH * y + x] = (rgb << 8) | 0xff;
}

void bmp_clear(uint32_t rgb) {
	uint32_t *buf = (uint32_t *)((uintptr_t)screen_buffer);
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
		buf[i] = rgb;
	}
}

int bmp_screen_height() {
	return 480;
}

int bmp_screen_width() {
	return 720;
}
