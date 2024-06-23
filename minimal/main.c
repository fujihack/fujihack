#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <fujihack.h>
#include <ff_io.h>
#include <ff_screen.h>
#include <hijack.h>

extern int sys_beep(int type);

void entry() {
	//int x = sys_selftimer_led(0xfa, 0xfa);

	while (1);

	((uint32_t *)0x01d039a8)[0] = ((uint32_t *)0x80000000)[0];
	((uint32_t *)0x01d039a8)[1] = 0x0;

	//strcpy((char*)MEM_PTP_TEXT, "Hello, World");
}
