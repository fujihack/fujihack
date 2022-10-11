// This will provide POSIX wrappers over Fujifilm RTOS functions
// for compatibility.

#include <stdio.h>

#include "fujifilm.h"
#include "fujihack.h"

FILE *fopen(const char *pathname, const char *mode) {
	fuji_toggle();
	void *fp = fuji_fopen(FUJI_FOPEN_HANDLER, pathname, 1);
	fuji_toggle();
	fuji_zero();

	return (FILE*)fp;
}

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
	fuji_toggle();
	fuji_fwrite(FUJI_FWRITE_HANDLER, stream, size * nmemb, ptr);
	fuji_toggle();
	fuji_zero();

	// Innacurate
	return size * nmemb;
}

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	fuji_toggle();
	fuji_fread(FUJI_FREAD_HANDLER, stream, size * nmemb, ptr);
	fuji_toggle();
	fuji_zero();

	// Innacurate
	return size * nmemb;
}

int fclose(FILE *stream) {
	fuji_toggle();
	fuji_fclose(FUJI_FCLOSE_HANDLER, stream, 0, (char*)0);
	fuji_toggle();
	fuji_zero();
	return 0;
}

// This is more practical as a macro
// Put in fujijack.h?
#define snprintf(str, size, format, ...) \
	sqlite_snprintf(size, str, format, __VA_ARGS__) 

