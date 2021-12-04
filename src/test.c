// This code is injected into the Fujifilm camera

#ifndef MODEL_NAME
	#include "../model/xf1.h"
#endif

#include <string.h>

void entry() {
	char *model = (char *)MEM_MODEL_TEXT;
	strcpy(model, "Hello World");
}
