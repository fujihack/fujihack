// Defines fujihack specific utils, menus
#ifndef FUJIHACK_H
#define FUJIHACK_H

#include <stdint.h>

void memory_dump(char file[], uintptr_t location);
int cardspeed();
void enable_script_flag();

#define SCREENWRT(x, y, ...) \
	{char scdbg_buffer[64]; \
	sqlite_snprintf(sizeof(scdbg_buffer), scdbg_buffer, __VA_ARGS__); \
	fuji_screen_write(scdbg_buffer, x, y, 0, 7);}

#define SCREENDBG(...) SCREENWRT(1, 1, __VA_ARGS__)

// Menus init, typically not called
void fujihack_init();

#endif
