// This code is injected into the Fujifilm camera

#ifndef MODEL_NAME
	#include "../model/xf1.h"
#endif

#include <string.h>
#include "sqlite.h"

int dump_test();

void entry() {
	char *model = (char *)MEM_MODEL_TEXT;
	int a = dump_test(model, 0, 0x10);
	sqlite_snprintf(20, model, "fart, %d", a);
}
