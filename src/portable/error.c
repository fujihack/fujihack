// perror equivelants - or maybe similar to what win32 has
// Copyright (C) 2022-2023 Frontier by Daniel C - Apache License
#include <stdio.h>
#include <stdarg.h>
#include <bmp.h>

// TODO: This causes race condition
static char error_buffer[128];

void sys_report_err(const char* format, ...) {
	va_list args;
	va_start(args, format);
	vsnprintf(error_buffer, sizeof(error_buffer), format, args);
	va_end(args);
}

char *sys_get_error() {
	return error_buffer;
}

int fault_screen() {
	bmp_clear(0x33bb);

	bmp_string(10, 10, "A problem has been detected and FrontierOS has been", 0xffffff);
	bmp_string(10, 30, "shut down to prevent damage to your device.", 0xffffff);

	while (1) {}

	return 0;
}
