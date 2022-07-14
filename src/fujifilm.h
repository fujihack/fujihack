#ifndef FUJI_H
#define FUJI_H

/*

Fujifilm uses 4 bytes per pixel, multiple layer display system.
Each pixel is your typical hex code #aabbcc, with the
last 2 bytes are transparency (????)

*/

// Screen
#define COL_BLACK 0x00000000
#define COL_WHITE 0xffffffff

// RTOS malloc, used by some wlan functions.
// mode is generally -1
unsigned int fuji_malloc(int n, void *addr, int mode);

// Returns current drive (DOS style)
char fuji_drive();

// Screen text
#define TEXT_BLACK 7
#define TEXT_WHITE 1

// Write ASCII text rows to screen
void fuji_screen_write(char string[], int x, int y, int foreground_color, int background_color);

// Delete text buffer, does not take effect until screen updates
void fuji_discard_text_buffer();

void *fuji_fopen(uint32_t handler, char string[]);
void *fuji_fwrite(uint32_t handler, void *fp, int n, void *data);
void *fuji_fclose(uint32_t handler, void *fp, int x, char *y);

// Weird timing functions required by file API
void fuji_toggle();
void fuji_zero();

#endif
