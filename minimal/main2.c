#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <fujihack.h>
#include <io.h>
#include <rst.h>
#include <sqlite.h>
#include <screen.h>
#include <task.h>

typedef void func(void);

void entry() {
	func* f = (func*)fh_load();
	f();

	strcpy((char*)MEM_PTP_TEXT, "finished execution");
}
