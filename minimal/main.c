#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <fujihack.h>
#include <ff_io.h>
#include <ff_screen.h>
#include <hijack.h>

void entry() {
	strcpy((char*)MEM_PTP_TEXT, "Hello, World");
}
