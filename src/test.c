// This code is injected into the Fujifilm camera

#ifndef MODEL_NAME
	#include "../model/xf1.h"
#endif

#include <string.h>

extern int i2;

void entry() {
	unsigned char *addr = (unsigned char *)0x00000000;

	char *model = (char *)MEM_MODEL_TEXT;

	for (int i = 0; i < 20; i++) {
		model[i] = addr[i2];
		i2++;
	}
}
