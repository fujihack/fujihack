#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <fujifilm.h>
#include <rst.h>

#include <fujihack.h>
#include <sqlite.h>
#include <screen.h>
#include <hijack.h>

void entry() {
	strcpy((char*)MEM_PTP_TEXT, "Hello, World");
}
