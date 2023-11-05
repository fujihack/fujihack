#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys.h>
#include <bmp.h>
#include <buttons.h>

void pt_pixel(int x, int y, int col) {
	bmp_pixel(x + 0, y + 0, col);
}

uint32_t pt_colors[6] = {
	0xa9cdcf, // background color
	0x00994a,
	0x0362fc,
	0xfc03db,
	0xfc0303,
	0x58B500,
};

// #define PT_MAX_WIDTH 40
// #define PT_MAX_HEIGHT 40

#include "ptetris.h"

int main() {
	sys_init_bmp();

	memset(&pt_main_field, 0, sizeof(struct PtField));

	int last = 0;
	while (1) {
		if (last > 10) {
			if (pt_step()) {
				return 0;
			}

			last = 0;
		}

		last += 1;

		if (sys_check_key(SYS_BUTTON_DOWN)) {
			pt_handle_input(PT_DOWN);
			msleep(50);
		} else if (sys_check_key(SYS_BUTTON_UP)) {
			pt_handle_input(PT_ROT);
			msleep(50);
		} else if (sys_check_key(SYS_BUTTON_RIGHT)) {
			pt_handle_input(PT_RIGHT);
			msleep(50);
		} else if (sys_check_key(SYS_BUTTON_LEFT)) {
			pt_handle_input(PT_LEFT);
			msleep(50);
		} else if (sys_check_key(SYS_BUTTON_QUIT)) {
			return 0;
		} else {
			goto e;
		}

		msleep(40);
		e:;
		pt_render();
		bmp_apply();
		//msleep(400);
	}

	return 0;
}

