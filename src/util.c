#include <string.h>

#include "fujihack.h"
#include "fujifilm.h"
#include "sqlite.h"
#include "screen.h"
#include "hijack.h"

#define DUMP_SIZE_MB 256
#define DUMP_SIZE DUMP_SIZE_MB * 1000 * 1000

void memory_dump(char file[], uintptr_t location) {
	char buffer[32];
	sqlite_snprintf(sizeof(buffer), buffer, "Dumping %uMB RAM", DUMP_SIZE_MB);
	fuji_screen_write(buffer, 1, 1, 0, 7);
	fuji_screen_write("Will lock up", 1, 2, 0, 7);

	uint8_t *mem = (uint8_t*)location;

	file[0] = fuji_drive();

	fuji_toggle();
	void *fp = fuji_fopen(FUJI_FOPEN_HANDLER, file, 1);
	fuji_toggle();
	fuji_zero();

	fuji_toggle();
	fuji_fwrite(FUJI_FWRITE_HANDLER, fp, DUMP_SIZE, mem);
	fuji_toggle();
	fuji_zero();

	fuji_toggle();
	fuji_fclose(FUJI_FCLOSE_HANDLER, fp, 0, (char*)0);
	fuji_toggle();
	fuji_zero();

	fuji_screen_write("Done.", 1, 3, 0, 7);
}

void enable_script_flag() {
	SCREENDBG("Flag 0xa2: %u", ((uint8_t*)(MEM_EEP_START + 0xa2))[0])
	SET_EEP(0xa2, 0x2)
	fuji_apply_eeprom();
}

int test = 0;
int timer_stayalive = 1;
uint32_t timer = 0;
void timer_callback() {
	while (timer_stayalive) {
		fuji_task_sleep(10);
		timer++;
	}

	fuji_wait_task_stop(test);
}

#define TEST_SIZE (1 * 1000 * 1000)

int cardspeed() {
	char file[] = "X:\\TEMP.BIN";
	file[0] = fuji_drive();

	SCREENWRT(1, 1, "Timer start")

	fuji_toggle();
	void *fp = fuji_fopen(FUJI_FOPEN_HANDLER, file, 1);
	fuji_toggle();
	fuji_zero();

	if (fuji_wait_task_start(0, 1, timer_callback, &test)) {
		return 1;
	}
	

	fuji_toggle();
	fuji_fwrite(FUJI_FWRITE_HANDLER, fp, TEST_SIZE, (void*)0x0);
	fuji_toggle();
	fuji_zero();

	fuji_toggle();
	fuji_fclose(FUJI_FCLOSE_HANDLER, fp, 0, (char*)0);
	fuji_toggle();
	fuji_zero();

	SCREENWRT(1, 2, "%dms to write 1mb", timer * 10)
	timer_stayalive = 0;

	return 0;
}
