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

// TODO: Allow non UI hijack_menu states (modules, button presses)
// Prevent binary from being loaded every time
int loaded = 0;

int main_menu() {
	ui_text("Fujihack pre-release - Written by Daniel Cook", 0xffffff);
	ui_text("Running on the " MODEL_NAME, 0xffffff);

	if (ui_button("Quit all")) {
		return 1;
	}

	if (ui_button("Test button 1")) {
		
	}

	if (ui_button("Test button 2")) {
		
	}

	ui_text("Active hacks:", 0xffff11);
	ui_text("- Shutter button remap", 0xffff11);
	ui_text("- Extend record limit", 0xffff11);

	struct FujiInputMap *m = (struct FujiInputMap *)MEM_INPUT_MAP;
	char buffer[64];
	sprintf(buffer, "[-] Keys: %X %X", m->key_code, m->key_status);
	ui_text(buffer, 0xffff11);

	return 0;
}

int hijack_menu() {
	if (!loaded) {
		sys_init_bmp();
		sys_init_mem();
		ui_reset();
		loaded = 1;

		fh_infinite_record_limit();
		fh_start_remap_shutter();

		// First keypress after pressing menu should be from "Press any key to continue"
		// The menu will not be rendered until 
		ui_reset();
		main_menu();
		return 1;
	}

	struct FujiInputMap *m = (struct FujiInputMap *)MEM_INPUT_MAP;
	if (m->key_code == KEY_DISPBACK) {
		if (m->key_status == 0x80) {
			// NOP out dev mmode hijack function to disable menu
			char export[] = {
				0x0, 0x0, 0xa0, 0xe3,   // mov r0, #0x0
				0x1e, 0xff, 0x2f, 0xe1, // bx lr
			};
			memcpy((void *)MEM_RUN_DEV_MODE, export, sizeof(export));

			// Press back to exit instax menu, general menu
			fuji_press_key_alias("DISP_B", "ON");
			fuji_press_key_alias("DISP_B", "OFF");
			fuji_press_key_alias("DISP_B", "ON");
			fuji_press_key_alias("DISP_B", "OFF");
		}

		return 1;
	}

	if (m->key_status == 0x0) {
		if (ui_frame(main_menu) == 1) {
			// Quit button does nothing for now
		}
	}

	return 1;
}

void intro_screen() {
	sys_init_bmp();
	bmp_clear(0);
	//bmp_string(50, 10, "Press any button to continue.", 0xffffffff);
}

int menu_dont_load() {
	fuji_rst_config1(0xf);
	fuji_rst_config2(0xf);
	fuji_rst_write(3, 3, "Loaded");

	entry();
	
	return 0;
}

void entry() {
	// Patch dev mode menu task with custom call
	uint32_t inst[] = {
		0xe28f0004, // adr r0, x
		0xe5900000, // ldr r0, [r0]
		0xe12fff10, // bx r0
		(uint32_t)hijack_menu,
	};

	if (memcmp((void *)MEM_RUN_DEV_MODE, inst, sizeof(inst))) {
		memcpy((void *)MEM_RUN_DEV_MODE, inst, sizeof(inst));
		//intro_screen();
	}

	// Patch instax menu with quick call so entire file isn't loaded every time
	uint32_t inst2[] = {
		0xe92d8002, // push {r1, pc}
		0xe59f1004, // ldr r1, x
		0xe12fff31, // blx r1
		0xe8bd4002, // pop {r1, lr}
		(uint32_t)menu_dont_load
	};

	memcpy((void *)MEM_INSTAX_MENU, inst2, sizeof(inst2));
}
