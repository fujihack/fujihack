#include <stdio.h>
#include <stdint.h>
#include <bmp.h>
#include <io.h>
#include <rst.h>

#include <doomkeys.h>
#include <m_argv.h>
#include <doomgeneric.h>

int last_input = 0;
int last_key_status = 0;

int indicator = 0;

#define MAX_QUEUE 20
struct Queue {
	int keys[20];
	uint8_t status[20];
	int length;
}queue;

void DG_Init() {
	queue.length = 0;
	printf("Init bmp\n");
}


void DG_DrawFrame() {
	// if (inited == 0) {
		// sys_init_bmp();
		// inited = 1;
	// }

	int x2 = 0;
	int y2 = 0;
	for (int x = 0; x < DOOMGENERIC_RESX * DOOMGENERIC_RESY; x++) {
		uint32_t col = DG_ScreenBuffer[x];
		bmp_pixel(30 + x2, 30 + y2, col);
		if (x2 == DOOMGENERIC_RESX - 1) {
			x2 = 0;
			y2++;
		} else {
			x2++;
		}
	}

	if (indicator) {
		bmp_pixel(5, 5, 0xffffffff);
	} else {
		bmp_pixel(5, 5, 0);
	}

	indicator = !indicator;

	struct FujiInputMap *f = (struct FujiInputMap *)MEM_INPUT_MAP;
	if (f->key_status == 0) {
		bmp_pixel(10, 5, 0xffffffff);
	} else {
		bmp_pixel(10, 5, 0x0);
	}

	if (queue.length < 20) {
		queue.keys[queue.length] = f->key_code;
		queue.status[queue.length] = f->key_status == 0;
		queue.length++;
	}

	bmp_apply();
}

void DG_SleepMs(uint32_t ms) {
	//uart_str("SleepMs");
	fuji_task_sleep(ms);
}

uint32_t DG_GetTicksMs() {
	//uart_str("GetTicks");
	return sys_get_ticks();
}

void DG_SetWindowTitle(const char * title) {
	puts(title);
}

int get_doom_key(uint32_t f) {
	switch (f) {
	case KEY_RIGHT:
		return KEY_RIGHTARROW;
	case KEY_LEFT:
		return KEY_LEFTARROW;
	case KEY_UP:
		return KEY_UPARROW;
	case KEY_DOWN:
		return KEY_DOWNARROW;
	case KEY_OK:
		return KEY_ENTER;
	case KEY_SHUTTER1:
	case KEY_SHUTTER2:
		return KEY_FIRE;
	case KEY_DISPBACK:
		return KEY_USE;
	}

	return 0;
}

int DG_GetKey(int* pressed, unsigned char* key) {
	struct FujiInputMap *f = (struct FujiInputMap *)MEM_INPUT_MAP;

	bmp_fill_rect(20, 0, 100, 20, 0x0);
	font_print_char(20, 0, '0' + queue.length, 0xffffff);

	if (queue.length) {
		*key = get_doom_key(queue.keys[queue.length - 1]);
		*pressed = queue.status[queue.length - 1];
		queue.length--;
		return 1;
	} else {
		*key = 0;
		*pressed = 0;
		return 0;
	}
}
