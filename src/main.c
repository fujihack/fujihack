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

#if 0
todo: try 
-fomit-frame-pointer
-fno-omit-frame-pointer
without mcpu, marm, o2
move linker sections around
-fcheck-pointer-bounds
#endif

void entry(uintptr_t base) {
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

	#if 0

	printf("Init\n");

	printf("Running doom...");
	D_DoomMain();

	#endif

}
