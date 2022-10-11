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

#ifdef MEM_EEP_START
void enable_script_flag() {
	SCREENDBG("Flag 0xa2: %u", ((uint8_t*)(MEM_EEP_START + 0xa2))[0])
	SET_EEP(0xa2, 0x2)
	fuji_apply_eeprom();
}
#endif

// Card benchmarking
#define TEST_WRITES 1024
#define TEST_TIMER 100
#define TEST_MB 128
#define TEST_SIZE (TEST_MB * 1000 * 1000)

int timer_stayalive = 0;
uint32_t timer = 0;
void timer_callback() {
	while (1) {
		if (timer_stayalive) return;
		fuji_task_sleep(TEST_TIMER);
		timer += TEST_TIMER;
	}
}

int cardspeed() {
	char file[] = "X:\\TEMP.BIN";
	file[0] = fuji_drive();

	SCREENWRT(1, 1, "Timer start")

	fuji_toggle();
	void *fp = fuji_fopen(FUJI_FOPEN_HANDLER, file, 1);
	fuji_toggle();
	fuji_zero();

	if (fuji_wait_task_start(0, 0, timer_callback, 0)) {
		return 1;
	}
	
	for (int i = 0; i < TEST_WRITES; i++) {
		fuji_toggle();
		fuji_fwrite(FUJI_FWRITE_HANDLER, fp, TEST_SIZE / TEST_WRITES, (void*)0x0);
		fuji_toggle();
		fuji_zero();
	}

	timer_stayalive = 1;

	fuji_toggle();
	fuji_fclose(FUJI_FCLOSE_HANDLER, fp, 0, (char*)0);
	fuji_toggle();
	fuji_zero();

	SCREENWRT(1, 2, "Speed test: %dmbs", 1000 / (timer / TEST_MB))
	return 0;
}
