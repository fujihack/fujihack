#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <sys.h>

//#include "io.h"
//#include "rst.h"

#include "sqlite.h"
//#include "screen.h"
//#include "hijack.h"
//#include <mjs.h>

void entry(uintptr_t base) {
	sys_init_mem();

	sprintf(buffer, "demo: %X", 123);
	uart_str(buffer);
}
