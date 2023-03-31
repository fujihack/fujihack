#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <sys.h>

//#include "io.h"
//#include "rst.h"

#include "sqlite.h"
//#include "screen.h"
//#include "hijack.h"
//#include <mjs.h>

#include <doomkeys.h>
#include <m_argv.h>
#include <doomgeneric.h>
#include <buttons.h>

int buf[10];

void func() {
	sys_init_bmp();
	bmp_clear(0xff000000);

	fuji_io_lock(7, 8, 0);
	sys_init_mem();

	uart_str("785k of DOOM is on cam!");

	char *args[] = {"doom", "-iwad", "C:\\doom1.wad"};
	myargc = 3;
	myargv = args;

	printf("M_FindResponseFile()\n");
	M_FindResponseFile();

	printf("Creating doom context...\n");
	dg_Create();

	printf("Running doom...");
	D_DoomMain();

	puts("END");	
}

void entry(uintptr_t base) {
	//font_print_string(10, 10+7+2, "This is a test.", 0xffffff00);
	//fuji_screen_write_("Hello new", 2, 1, 0, 7);
	//fuji_screen_write_("Hello new2", 2, 2, 0, 7);
	//fuji_screen_write_("Hello new3", 2, 3, 0, 7);
	//fuji_screen_write("Hello old", 1, 3, 0, 7);
	func();
	//fuji_wait_task_start(0, 0, &func, buf);
}
