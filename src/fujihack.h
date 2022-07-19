#ifndef FUJIHACK_H
#define FUJIHACK_H

#define SCREENDBG(...) \
	{char buffer[32]; \
	sqlite_snprintf(sizeof(buffer), buffer, __VA_ARGS__); \
	fuji_screen_write(buffer, 1, 1, 0, 7);}

void fujihack_init();

#endif
