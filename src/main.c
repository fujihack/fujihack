#ifndef MODEL_NAME
	#include "../model/xf1_101.h"
#endif

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "fujifilm.h"
#include "rst.h"

#include "fujihack.h"
#include "sqlite.h"
#include "screen.h"
#include "hijack.h"
#include "parasite.h"

int tetris_task();

void entry() {
#if 0
	// Why is this crashing? Worked before...
	char buffer[32];
	int r = fuji_dir_open("C:\\", "*", buffer);
	r = fuji_dir_next(buffer);
	SCREENDBG("Hello, %d", r)
#endif
#if 0
	write_file("X:\\DCAA\\auto_act.scr",
		"WAITSET 123\r\n"
	);

	run_auto_act();
#endif
#if 0
	fuji_discard_text_buffer();
	generate_branch(MEM_SHOW_PHOTO_PROPERTIES, (uintptr_t)&tetris_task, (uint8_t*)MEM_SHOW_PHOTO_PROPERTIES);
#endif
#if 1
	char *x = (char*)MEM_MODEL_TEXT;
	sqlite_snprintf(16, x, "Hello World");
#endif
#if 0
	memory_dump("X:\\RAM.BIN", 0x40000000);
#endif
}
