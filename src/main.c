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

void entry() {
#if 0
	cardspeed();
#endif
#if 1
	strcpy((char*)MEM_MODEL_TEXT, "Hello, World");
#endif
#if 0
	memory_dump("X:\\RAM.BIN", 0x0);
#endif
}
