// This code is injected into the Fujifilm camera

#ifndef MODEL_NAME
	#include "../model/xf1.h"
#endif

#include <string.h>
#include "sqlite.h"
#include "fujifilm.h"

void entry() {
	int a = 0;
	int b = rtos_malloc(10, &a, 0xffffffff);

	char *model = (char *)MEM_MODEL_TEXT;
	sqlite_snprintf(0x20, model, "p=%x, r=%x", a, b);
}

