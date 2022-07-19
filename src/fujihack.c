#ifndef MODEL_NAME
	#include "../model/xf1_101.h"
#endif

#include "fujihack.h"

#include <string.h>
#include <stdint.h>
#include "fujifilm.h"
#include "sqlite.h"

void fujihack();

// Main FujiHack Menu

enum FujiKey {
	KEY_UP = 0x2,
	KEY_DOWN = 0x3,
	KEY_RIGHT = 0x5,
	KEY_LEFT = 0x4,
	KEY_DISPBACK = 0x9,
	KEY_EFN = 0x36,
	KEY_SCROLL_DOWN = 0x3a,
	KEY_FN = 0x2f,
};


struct Menu {
	char curr_screen;
	uint8_t screens;
	char cursor;
	uint8_t i;
};

void fujihack_init() {
	// Soon: figure out multitasking
	fujihack();
}

void menuPrint(struct Menu *menu, char string[]) {
	if (menu->i == menu->cursor) {
		fuji_screen_write(string, 1, 2 + menu->i, 3, 7);
	} else {
		fuji_screen_write(string, 1, 2 + menu->i, 0, 7);
	}

	menu->i++;
}

void fujihack() {
	struct Menu menu;
	menu.curr_screen = 0;
	menu.screens = 1;
	menu.cursor = 0;

	struct FujiInputMap *k = (struct FujiInputMap*)MEM_INPUT_MAP;

	k->key_code = 128;

	goto draw;

	while (1) {
		char buffer[32];

		if (k->key_status != 128) {
			switch (k->key_code) {
			case KEY_DOWN:
				menu.cursor++;
				break;
			case KEY_UP:
				menu.cursor--;
				break;
			case KEY_RIGHT:
				if (menu.curr_screen + 1 >= menu.screens) {
					menu.curr_screen++;
				}
				break;
			case KEY_LEFT:
				if (menu.curr_screen - 1 <= menu.screens) {
					menu.curr_screen++;
				}
				break;
			case KEY_DISPBACK:
				fuji_screen_write("FujiHack Quitting", 1, 1, 10, 7);
				fuji_discard_text_buffer();
				return;
			default:
				continue;
			}
		}

		draw:
		menu.i = 0;
		switch (menu.curr_screen) {
		case 0:
			fuji_screen_write("FujiHack Menu", 1, 1, 10, 7);

			menuPrint(&menu, "FujiHack By Daniel C");

			sqlite_snprintf(sizeof(buffer), buffer, "Key Code: %u", k->key_code);
			menuPrint(&menu, buffer);

			sqlite_snprintf(sizeof(buffer), buffer, "Key Down: %u", k->key_status != 128);
			menuPrint(&menu, buffer);

			sqlite_snprintf(sizeof(buffer), buffer, "Gryroscope: %u", k->gyro);
			menuPrint(&menu, buffer);

			sqlite_snprintf(sizeof(buffer), buffer, "Accelerometer: %u", k->accel);
			menuPrint(&menu, buffer);
		}

		fuji_task_sleep(100);
	}
}
