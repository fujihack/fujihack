// Main start file
// Copyright (C) 2022-2023 Frontier by Daniel C - Apache License
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#include <sys.h>
#include <bmp.h>
#include <ui.h>

int main_menu() {
	ui_text("FrontierOS software demo", 0xffffff);

	if (ui_button("Load ELF module")) {
		sys_load_app("app/tetris/tetris.elf");
	}

	return 0;
}

int ui_demo_loop() {
	ui_reset();
	sys_init_bmp();

	bmp_clear(0x0);

	while (1) {
		if (ui_frame(main_menu)) {
			return 0;
		}

		msleep(50);
	}
}

int entry() {
	sys_init_mem();
	sys_init_syms();
	log_cpu_info();

	return 0;
}
