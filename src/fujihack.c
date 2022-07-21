#ifndef MODEL_NAME
	#include "../model/xf1_101.h"
#endif


#include <string.h>
#include <stdint.h>
#include "fujihack.h"
#include "fujifilm.h"
#include "sqlite.h"
#include "hijack.h"

void fujihack();

// Main FujiHack Menu
#define FLASH_TASK_PATCH 0x0064632c
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


static struct Menu {
	char curr_screen;
	uint8_t screens;
	char cursor;
	uint8_t i;
}menu;

void fujihack_init(uintptr_t base) {
	menu.curr_screen = 0;
	menu.screens = 1;
	menu.cursor = 0;

	generate_call((uintptr_t)FLASH_TASK_PATCH, (uintptr_t)(base + fujihack), (uint8_t*)FLASH_TASK_PATCH);
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
	struct FujiInputMap *k = (struct FujiInputMap*)MEM_INPUT_MAP;
	char buffer[32];

	if (k->key_status != 128 && k->key_code == KEY_EFN) {
		k->key_status = 0;
		k->key_code = 0;
		fuji_task_sleep(10);
		goto menu_start;
	}

	return;

	uint8_t count = 0;
	while (1) {
		if (k->key_status != 128) {
			switch ((uint8_t)k->key_code) {
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
			case KEY_EFN:
				fuji_screen_write("Quitting", 1, 1, 10, 7);
				return;
			}
		}

		menu_start:;

		menu.i = 0;
		switch (menu.curr_screen) {
		case 0:
			fuji_screen_write("FujiHack Menu", 1, 1, 10, 7);

			menuPrint(&menu, "FujiHack By Daniel C");

			sqlite_snprintf(sizeof(buffer), buffer, "Key Code: %u", k->key_code);
			menuPrint(&menu, buffer);

			sqlite_snprintf(sizeof(buffer), buffer, "Key Down: %u", k->key_status);
			menuPrint(&menu, buffer);

			// sqlite_snprintf(sizeof(buffer), buffer, "X: %u", k->x);
			// menuPrint(&menu, buffer);

			sqlite_snprintf(sizeof(buffer), buffer, "Gryroscope: %u", k->gyro);
			menuPrint(&menu, buffer);

			sqlite_snprintf(sizeof(buffer), buffer, "Accelerometer: %u", k->accel);
			menuPrint(&menu, buffer);

			sqlite_snprintf(sizeof(buffer), buffer, "Renders: %u", count);
			menuPrint(&menu, buffer);
		}

		count++;
	}
}
