#ifndef FUJIHACK_H
#define FUJIHACK_H

#define SCREENDBG(...) \
	{char scdbg_buffer[64]; \
	sqlite_snprintf(sizeof(scdbg_buffer), scdbg_buffer, __VA_ARGS__); \
	fuji_screen_write(scdbg_buffer, 1, 1, 0, 7);}

void fujihack_init();

#endif
