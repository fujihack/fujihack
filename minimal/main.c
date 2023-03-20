#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <io.h>
#include <rst.h>
#include <sqlite.h>
#include <screen.h>

void entry() {
	strcpy((char*)MEM_PTP_TEXT, "Hello, World");
}
