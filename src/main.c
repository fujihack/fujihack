#ifndef MODEL_NAME
	#include "../model/xf1.h"
#endif

#include <string.h>
#include <stdint.h>

#include "sqlite.h"
#include "fujifilm.h"

void foo(uint32_t a, uint32_t b) {
	int r = fuji_file_do(0, "B:/asd");
	fuji_file_create(0x420d, 0, 0);
	
	char *model = (char *)MEM_MODEL_TEXT;
	sqlite_snprintf(0x20, model, "Params");
}

void entry() {
	fuji_fopen(&foo, "B:/asd", 0);
}

