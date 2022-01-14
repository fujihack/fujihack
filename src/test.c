#ifndef MODEL_NAME
	#include "../model/xf1.h"
#endif

#include <string.h>
#include "sqlite.h"
#include "fujifilm.h"

void entry() {
	char *model = (char *)MEM_MODEL_TEXT;
	sqlite_snprintf(0x20, model, "Hello, World, %u", 123);
}

