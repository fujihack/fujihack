// Some handy debugging macros and stuff
#ifndef FUJIHACK_H
#define FUJIHACK_H

#include <stdint.h>

#include "ff_sqlite.h"

struct FujihackState {
	uint8_t loaded;
	uint8_t active;
	void *keypress_addr;
};
extern struct FujihackState fh_state;

void fh_screendbg(const char *format, ...);

int fh_start_remap_shutter();
int fh_infinite_record_limit();

void fh_dump_ram();

//int cardspeed();
//void enable_script_flag();

#define SCREENWRT(x, y, ...) \
	{char scdbg_buffer[64]; \
	sqlite_snprintf(sizeof(scdbg_buffer), scdbg_buffer, __VA_ARGS__); \
	fuji_screen_write(scdbg_buffer, x, y, 0, 7);}

#define SCREENDBG(...) SCREENWRT(1, 1, __VA_ARGS__)

int fh_load();

#endif
