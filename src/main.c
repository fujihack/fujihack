#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>

#include <sys.h>
#include <ui.h>

#include <ff_io.h>
#include <ff_screen.h>

#include "fujihack.h"

int loaded = 0;

int main_menu() {
	ui_text("Fujihack pre-release - Written by Daniel Cook", 0xffffff);
	ui_text("Powered by FrontierOS", 0xffffff);

	if (ui_button("Quit all")) {
		return 1;
	}

	if (ui_button("Test button 1")) {
		
	}

	ui_text("Active hacks:", 0xffff11);
	ui_text("- Shutter button remap", 0xffff11);
	ui_text("- Extend record limit", 0xffff11);

	return 0;
}


int hijack_menu() {
	if (!loaded) {
		sys_init_mem();
		sys_init_bmp();
		ui_reset();
		loaded = 1;

		fuji_task_sleep(100);

		fh_infinite_record_limit();
		fh_start_remap_shutter();
	}

	struct FujiInputMap *m = (struct FujiInputMap *)MEM_INPUT_MAP;
	if (m->key_status == 0x0) {
		if (ui_frame(main_menu) == 1) {
			char export[] = {0x0, 0x0, 0xa0, 0xe3, 0x1e, 0xff, 0x2f, 0xe1, };
			memcpy((void *)MEM_RUN_DEV_MODE, export, sizeof(export));
		}
	}

	return 1;
}

void entry(uintptr_t base) {
	uint32_t inst[] = {
		0xe28f0004, // adr r0, x
		0xe5900000, // ldr r0, [r0]
		0xe12fff10, // bx r0
		(uint32_t)hijack_menu,
	};

	memcpy((void *)MEM_RUN_DEV_MODE, inst, sizeof(inst));
}
