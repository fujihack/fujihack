#ifndef FUJIHACK_H
#define FUJIHACK_H

#define SCREENDBG(...) \
	{char buffer[32]; \
	sqlite_snprintf(sizeof(buffer), buffer, __VA_ARGS__); \
	fuji_screen_write(buffer, 1, 1, 0, 7);}

#define PATCH32(addr, val) ((uint32_t*)addr)[0] = (uint32_t)val;
#define PATCH8(addr, val) ((uint8_t*)addr)[0] = (uint8_t)val;

#define KILLFUNC(addr) ((uint32_t*)addr)[0] = 0xe12fff1e;

void fujihack_init();

#endif
