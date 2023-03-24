#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <io.h>
#include <rst.h>
#include <sqlite.h>
#include <screen.h>

void entry() {
typedef void func(void);
	//sqlite_snprintf(64, (char *)MEM_PTP_TEXT, "Hello, world %s", "asd");
	strcpy((char*)MEM_PTP_TEXT, "Hello, World");
	func* f = (func*)fh_load();
	f();
}
