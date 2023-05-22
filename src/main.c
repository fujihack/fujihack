#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>

#include <sys.h>
#include <io.h>
#include <rst.h>
#include <ui.h>

#include "fujihack.h"

int main_menu() {
	ui_text("FrontierOS software demo", 0xffffff);

	if (ui_button("Render an image")) {
	}

	if (ui_button("Load ELF module")) {
		//sys_load_app("app/tetris/tetris.elf");
	}

	return 0;
}


int hijack_menu() {
	struct FujiInputMap *m = (struct FujiInputMap *)MEM_INPUT_MAP;
	if (m->key_status == 0x80) {
		ui_frame(main_menu);
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

	sys_init_mem();
	sys_init_bmp();

	ui_reset();
}
