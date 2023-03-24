#include <stdarg.h>
#include <stdio.h>

#include "io.h"
#include "rst.h"
#include "sqlite.h"
#include "screen.h"

// int errno_ = 0;
// 
// void *__errno() {
	// return &errno_;
// }

int col_y = 1;
void uart_str(char *string) {
	if (col_y == 10) {
		// TODO: clear layers manually
		//0x16facb4
		col_y = 0;
	}

	fuji_screen_write(string, 1, col_y, 0, 7);
	col_y++;

	fuji_task_sleep(100);
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

