// Basic button remapping in a background task
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <fujihack.h>
#include <ff_io.h>
#include <ff_task.h>

static struct FujiTaskBuffer buf;

//static int last_input = 0;
//static int last_key_status = -1;

#define COUNTDOWN 7
static int seconds_held = 0;

static void remap_func() {
	struct FujiInputMap *f = (volatile struct FujiInputMap *)MEM_INPUT_MAP;

	// Countdown to shutter after 7 seconds
	if (f->key_code == 0x82e && f->key_status == 0) {
		if (!fh_state.active) fh_screendbg("%d", seconds_held);
		seconds_held--;

		if (seconds_held == 0) {
			fuji_press_key_alias("S2", "ON");
			fuji_press_key_alias("S2", "OFF");
			seconds_held = COUNTDOWN;
		}
	}

	// // Listen for OK
	// if (last_input == 0x816 && f->key_code == 1 && f->key_status == 0 && last_key_status == 0) {
		// fuji_press_key_alias("S2", "ON");
		// fuji_press_key_alias("S2", "OFF");
		// last_input = 0;
		// last_key_status = -1;
	// }
// 
	// // Listen to shutter button
	// if (f->key_status == 0 && f->key_code != 0x82e) {
		// last_input = f->key_code;
		// last_key_status = 0;
	// }
}

int fh_start_remap_shutter() {
	seconds_held = COUNTDOWN;
	fuji_wait_task_start(500, 1, &remap_func, &buf);
}
