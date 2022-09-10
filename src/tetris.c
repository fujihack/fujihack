#include <stdint.h>

// This code is pure JANK, kind of
// https://github.com/petabyt/ptetris/tree/fujihack-xf1
// This code is meant to be called by show_photo_properties(), via a memory patch:
// generate_branch(MEM_SHOW_PHOTO_PROPERTIES, (uintptr_t)&tetris_task, (uint8_t*)MEM_SHOW_PHOTO_PROPERTIES);


#include "fujifilm.h"
#include "sqlite.h"

#define PT_CUSTOM_DRAW_BLOCK

uint8_t txt_rows[40][40];

void pt_draw_block(int bx, int by, int col) {
	txt_rows[by][bx] = (uint8_t)col;
}

#include "../../ptetris/ptetris.h"

void tetris_render() {
	// TODO: document
	FUN_011d2704(0xd);
	FUN_011fbb38(10);

	char colors[] = ".@#X8#@@";

	char line[32];
	for (int y = 1; y < 16; y++) {
		int i = 0;
		for (int x = 1; x < 16; x++) {
			line[i] = colors[txt_rows[x][y]];
			line[i + 1] = colors[txt_rows[x][y]];
			i += 2;
		}

		line[i] = '\0';

		uilib_print(1, y, line);
	}
}

int tetris_renders = 0;

void tetris_task() {
	struct FujiInputMap *k = (struct FujiInputMap*)MEM_INPUT_MAP;

	#define FLAT 0xA80

	int status = PT_NORMAL;

	if (tetris_renders == 10) {
		if (k->gyro == -1) {
			pt_handle_input(PT_ROT);
		} else if (k->gyro >= FLAT + 50) {
			pt_handle_input(PT_RIGHT);
		} else if (k->gyro <= FLAT - 50) {
			pt_handle_input(PT_LEFT);
		}

		tetris_renders = 0;
		status = pt_step();
	}

	// Increase entropy
	pt_rand_x += k->gyro;

	tetris_render();

	pt_render();
	char buffer[32];
	if (status == PT_NORMAL) {
		sqlite_snprintf(32, buffer, "Made by Daniel Cook. Score: %d", pt.score);
	} else if (status == PT_GAME_OVER) {
		sqlite_snprintf(32, buffer, "GAME OVER!!");
	}
	fuji_screen_write(buffer, 1, 10, 7, 1);

	tetris_renders++;
}
