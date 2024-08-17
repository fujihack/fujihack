// Basic button remapping in a background task
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <fujihack.h>
#include <ff_io.h>
#include <ff_task.h>
#include <ff_soc.h>

static struct FujiTaskBuffer buf;

static void remap_func() {
	volatile struct GpioPort *port = &((volatile struct GpioPort *)0xfff89000)[0];

	// Check Shutter and CMD dial
	if ((port->input & (1 << 2)) == 0) {
		if ((port->input & (1 << 10)) == 0) {
			fuji_press_key_alias("S2", "ON");
			fuji_press_key_alias("S2", "OFF");
		}
	}
}

int fh_start_remap_shutter() {
	fuji_wait_task_start(500, 1, &remap_func, &buf);
}
