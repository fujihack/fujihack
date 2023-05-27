#include <stdint.h>

#include "ff_io.h"
#include "ff_screen.h"

uintptr_t screen_buffer;
int sys_init_bmp() {
	// Write some permanent text so that a new layer is always present
	fuji_screen_write("...", 1, 1, 0, 7);

	fuji_task_sleep(500);

	// uintptr_t *ptr = (uintptr_t *)(MEM_OPENGL_BUFFERS);
	// if (ptr[0] > 0x40000000) {
		// screen_buffer = ptr[0];
	// } else {
		// screen_buffer = ptr[1];
	// }
}

int bmp_apply() {
	fuji_task_sleep(1);
}

void bmp_pixel(int x, int y, uint32_t rgb) {
	uintptr_t *ptr = (uintptr_t *)(MEM_OPENGL_BUFFERS);
	screen_buffer = ptr[1];

	uint32_t *buf = (uint32_t *)((uintptr_t)screen_buffer);
	buf[SCREEN_WIDTH * y + x] = (rgb << 8) | 0xff;
}

void bmp_clear(uint32_t rgb) {
	uintptr_t *ptr = (uintptr_t *)(MEM_OPENGL_BUFFERS);
	screen_buffer = ptr[1];

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
