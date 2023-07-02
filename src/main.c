#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>

#include <sys.h>
#include <ui.h>
#include <bmp.h>

#include <ff_io.h>
#include <ff_screen.h>
#include <ff_task.h>

#include "fujihack.h"

// TODO: Allow non UI hijack_menu states (modules, button presses)
// Prevent binary from being loaded every time
struct FujihackState fh_state = {0};

struct FujiTaskBuffer test_task = {0};
int test_rgb = 0x0;
void test_task_loop() {
	char buffer[128];
	sprintf(buffer, "Task: %d %d", test_task.a, test_task.b);
	bmp_fill_rect(100, 100, 100, 100, test_rgb);
	bmp_string(300, 250, buffer, -1);
	test_rgb += 0x111111;
}

int main_menu() {
	ui_text("Fujihack pre-release - Written by Daniel Cook", 0xffffff);
	ui_text("Running on the " MODEL_NAME, 0xffffff);

	if (ui_button("Test multitasking")) {
		fuji_wait_task_start(100, FUJI_TASK_REPEAT, test_task_loop, &test_task);
	}

	if (ui_button("Test loading app")) {
		sys_load_app("C:\\hello.elf");
		ui_text(sys_get_error(), 0xffffff);
	}

	ui_text("Active hacks:", 0xffff11);
	ui_text("- Shutter button remap", 0xffff11);
	ui_text("- Extend record limit", 0xffff11);

	struct FujiInputMap *m = (struct FujiInputMap *)MEM_INPUT_MAP;
	char buffer[64];
	sprintf(buffer, "[-] Keys: %X %X", m->key_code, m->key_status);
	ui_text(buffer, 0xffff11);

	uint8_t *s = sym("bmp_clear");
	sprintf(buffer, "Test sym for push inst -> %X: %02X %02X %02X %02X\n", s, s[0], s[1], s[2], s[3]);
	ui_text(buffer, 0xffff11);

	return 0;
}

int hijack_menu() {
	if (!fh_state.loaded) {
		sys_init_mem();
		sys_init_syms();
		sys_init_bmp();

		ui_reset();

		fh_state.loaded = 1;

		fh_infinite_record_limit();
		fh_start_remap_shutter();

		// First keypress after pressing menu should be from "Press any key to continue"
		// The menu will not be rendered until 
		ui_reset();
		bmp_clear(0);
		fh_state.active = 1;
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
			fh_state.active = 0;
		}

		return 1;
	}

	if (m->key_status == 0x0) {
		ui_reset();

		int key = ui_process_key();
		if (key == SYS_BUTTON_QUIT) {
			return 1;
		}

		bmp_clear(0);
		int rc = ui_update(main_menu);
	}

	return 1;
}

void intro_screen() {
	sys_init_bmp();
	bmp_clear(0);
	//bmp_string(50, 10, "Press any button to continue.", 0xffffffff);
}

void entry();

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
