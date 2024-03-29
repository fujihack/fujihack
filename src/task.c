// Test of standalone task loop
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <fujihack.h>
#include <ff_io.h>
#include <ff_screen.h>
#include <hijack.h>

int ping_playcont() {
	// For some reason, all tasks must 'ping' the playcont task. Otherwise
	// the camera will freeze. There is a function in the firmware to do this,
	// but I wanted to understand how to send events properly.
	uint32_t temp = 0;
	struct FujiEventReq req = {
		.event_code = 0xcf01,
		.current_tsk_id = fuji_get_task_id(),
		.target_tsk_id = 4,
		.target_tsk_id2 = 4,
		.unknown = &temp,
	};
	fuji_task_event(4, &req);
}

// Drop in replacement hack for sqlite task hijack
int test_task_hijack() {
	int d = 0;
	while (1) {
		bmp_clear(0xff0000ff);
		d++;
		fuji_task_sleep(40);
		ping_playcont();
	}
	return 4;
}
