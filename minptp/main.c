#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <ff_io.h>
#include <ff_sqlite.h>
#include <ff_screen.h>
#include <fujihack.h>

typedef void veener(void *ex, uint32_t sid, uint32_t obj, uint32_t offset, uint32_t r0, uint32_t r1, uint32_t r2);

void func(void *exe, uint32_t sid, uint32_t obj, uint32_t offset, uint32_t r0, uint32_t r1, uint32_t r2) {
	SCREENDBG("%d %d %d", obj, offset, r0);
	veener *x = (veener *)0x013dd7d4;
	x(exe, sid, obj, offset, r0, r1, r2);
}

void entry() {
	((uint32_t *)0x013decc4)[0] = func;
	//((uint32_t *)0x013d9bd0)[0] = 0xe3a03001;
	SCREENDBG("Hello, World");
}
