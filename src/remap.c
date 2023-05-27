#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <ff_io.h>

static struct FujiTaskBuffer buf;

static int last_input = 0;
static int last_key_status = -1;

static void remap_func() {
	struct FujiInputMap *f = (struct FujiInputMap *)MEM_INPUT_MAP;
	if (last_input == 0x816 && f->key_code == 1 && f->key_status == 0 && last_key_status == 0) {
		fuji_press_key_keyword("S2", "ON");
		fuji_press_key_keyword("S2", "OFF");
		last_input = 0;
		last_key_status = -1;
	}

	if (f->key_status == 0 && f->key_code != 0x82e) {
		last_input = f->key_code;
		last_key_status = 0;
	}
}

int fh_start_remap_shutter() {
	fuji_wait_task_start(100, 1, &remap_func, &buf);
}
