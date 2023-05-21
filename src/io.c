#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include <bmp.h>

#include "io.h"
#include "rst.h"
#include "sqlite.h"
#include "screen.h"

// Custom implementation of fuji_screen_write
#if 0
void fuji_screen_write_(char *text, int x, int y, int fg, int bg) {
	struct RstText *rst = (struct RstText *)MEM_TEXT_LAYERS;
	struct RstTextEntry *entry = MEM_TEXT_LAYERS + sizeof(struct RstText);
	entry[rst->length].y = y * 2 - 1;
	entry[rst->length].x = x;
	entry[rst->length].fg = bg;
	entry[rst->length].bg = fg;

	memset(entry[rst->length].unicode_string, 0x0, 66);

	int i;
	for (i = 0; i < 65; i++) {
		entry[rst->length].unicode_string[i * 2] = text[i];
		entry[rst->length].unicode_string[i * 2 + 1] = 0xe1;
		if (text[i] == '\0') {
			break;
		}
	}

	rst->length++;
	rst->active = 0;
	fuji_task_sleep(10);
	rst->active = 1;
}
#endif

int stop_logs = 0;
int col_y = 1;
void screen_log(char *string) {
	if (string == 0) return;
	if (string[0] == '@') return;

	char max[32];
	memcpy(max, string, 32);
	max[31] = '\0';

	bmp_string(10, 10 + (18 * col_y), max, 0xffffff);

	if (col_y == 24) {
		col_y = 0;
		bmp_clear(0);
	} else {
		col_y++;
	}

	fuji_task_sleep(0);
	bmp_apply();
}

void uart_str(char *string) {
	screen_log(string);
}

int printf(const char *format, ...) {
	char buffer[512];
	va_list aptr;

	va_start(aptr, format);
	int w = vsnprintf(buffer, sizeof(buffer), format, aptr);
	va_end(aptr);

	buffer[sizeof(buffer) - 1] = '\0';

	uart_str(buffer);

	return w;
}

int puts(const char *x) {
	uart_str(x);
	return 0;
}

int sys_putchar(int c) {
	return 0;
}
