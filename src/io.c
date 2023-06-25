#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include <bmp.h>

#include "ff_io.h"
#include "ff_task.h"
#include "ff_screen.h"
#include "ff_sqlite.h"

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


void uart_str(const char *string) {
	// TODO: Log?
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
