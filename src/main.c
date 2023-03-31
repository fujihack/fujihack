#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>

#include <sys.h>
#include <io.h>
#include <rst.h>

#include "fujihack.h"
#include "sqlite.h"

void entry(uintptr_t base) {
	sys_mem_init();
	SCREENDBG("Hello, World");
}
