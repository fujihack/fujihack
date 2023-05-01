#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>

#include <sys.h>
#include <io.h>
#include <rst.h>

#include "fujihack.h"
#include "sqlite.h"

void tramp() __attribute__((naked));
void tramp()
{
    __asm__ __volatile__(
        "push {ip, lr}\n"
        "mrs lr, spsr\n"
        "push {ip, lr}\n");

//    unsigned int ttbr0;
  //  asm volatile ("mrc p15, 0, %0, c2, c0, 0" : "=r" (ttbr0));

	font_print_string(100, 100, "SuperVisor call (SVC)", 0);

	__asm__ __volatile__(
        "pop {ip, lr}\n"
        "msr spsr_fsxc, lr\n"
        "ldm sp!, {ip, pc}^\n"
    );
}

void entry() {
	((uintptr_t *)0x28)[0] = tramp;
	sys_init_bmp();

	bmp_clear(-1);

	char buffer[512];
	sprintf(buffer, "Hello %x", 0x123);
	font_print_string(100, 200, buffer, 0);

	asm volatile("svc #1");
}
