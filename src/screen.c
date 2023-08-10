#include <stdint.h>

#include "ff_io.h"
#include "ff_screen.h"

uintptr_t screen_buffer;
int sys_init_bmp() {
	// Write some permanent text so that a new layer is always present
	//fuji_screen_write("...", 1, 1, 0, 7);

	//fuji_task_sleep(500);

	// uintptr_t *ptr = (uintptr_t *)(MEM_OPENGL_BUFFERS);
	// if (ptr[0] > 0x40000000) {
		// screen_buffer = ptr[0];
	// } else {
		// screen_buffer = ptr[1];
	// }
}

int bmp_apply() {
}

void bmp_pixel(int x, int y, uint32_t rgb) {
	// Fuji uses 3 buffers for double buffering. Need to paint to all 3 since I don't
	// know how to do double buffering.
	for (int i = 0; i < 3; i++) {
		volatile uintptr_t *ptr = (volatile uintptr_t *)(MEM_OPENGL_BUFFERS);
		screen_buffer = ptr[i];

		volatile uint32_t *buf = (volatile uint32_t *)((uintptr_t)screen_buffer);
		buf[SCREEN_WIDTH * y + x] = (rgb << 8) | 0xff;
	}
}

void bmp_clear(uint32_t rgb) {
	for (int i = 0; i < 3; i++) {
		volatile uintptr_t *ptr = (volatile uintptr_t *)(MEM_OPENGL_BUFFERS);
		screen_buffer = ptr[i];

		volatile uint32_t *buf = (volatile uint32_t *)((uintptr_t)screen_buffer);
		for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
			buf[i] = rgb;
		}
	}
}

int bmp_screen_height() {
	return SCREEN_HEIGHT;
}

int bmp_screen_width() {
	return SCREEN_WIDTH;
}
