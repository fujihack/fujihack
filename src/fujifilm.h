#ifndef FUJI_H
#define FUJI_H

/*

Fujifilm uses 4 bytes per pixel, multiple layer display system.
Each pixel is your typical hex code #aabbcc, with the
last 2 bytes are transparency (????)

*/

#define COL_BLACK 0x00000000
#define COL_WHITE 0xffffffff

// RTOS malloc, used by some wlan functions.
// mode is generally -1
unsigned int rtos_malloc(int n, void *addr, int mode);

// Returns current drive (DOS style)
char fuji_drive();

#if 0
// Posix wrappers around RTOS functions:
void malloc(int n) {
	void *addr;
	rtos_malloc(n, &addr, -1);
}
#endif

#endif
