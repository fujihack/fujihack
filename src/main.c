#ifndef MODEL_NAME
	#include "../model/xf1_101.h"
#endif

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "fujihack.h"
#include "fujifilm.h"
#include "sqlite.h"
#include "screen.h"
#include "hijack.h"
#include "parasite.h"

void entry() {
#if 0
	int r = fuji_dir_open("A:\\", "*", buffer);
	r = fuji_dir_next(buffer);
#endif
#if 0
	write_file("X:\\DCAA\\auto_act.scr",
		"WAITSET 123\r\n"
	);

	run_auto_act();
#endif
#if 0
	fujihack_init(base);
#endif
#if 1
	char *x = (char*)MEM_MODEL_TEXT;
	sqlite_snprintf(16, x, "Hello World");
#endif
#if 0
	memory_dump("X:\\RAM.BIN", 0x40000000);
#endif
}
