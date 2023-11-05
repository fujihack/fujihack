// Copyright (C) 2022-2023 Frontier by Daniel C - Apache License
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <sys.h>
#include <js.h>

void sys_debug(const char *format, ...) {
	char buffer[1024];
	va_list aptr;

	strcpy(buffer, "[FRNT] ");
	int len = strlen(buffer);

	va_start(aptr, format);
	vsnprintf(buffer + len, sizeof(buffer) - len, format, aptr);
	va_end(aptr);

	uart_str(buffer);
}

int printf(const char *format, ...) {
	char buffer[1024];
	va_list aptr;

	va_start(aptr, format);
	vsnprintf(buffer, sizeof(buffer), format, aptr);
	va_end(aptr);

	uart_str(buffer);

	return 0;
}

int puts(const char *x) {
	uart_str((char *)x);
	uart_char('\n');
	return 0;
}

int prompt_line() {
	char buffer[64];
	int curr = 0;
	while (1) {
		char c = getchar();
		if (c == (char)255) {
			exit(0);
		}

		buffer[curr] = c;

		if (c == '\n') {
			buffer[curr] = '\0';

			puts(buffer);
			return 0;
		}

		curr++;
	}
}
