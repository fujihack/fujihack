#include <stdint.h>

#include <sqlite.h>
#include <fujifilm.h>

char buffer[100];

char *_start() {
	char drive = fuji_drive();

	sqlite_snprintf(100, buffer, "Drive at dump is %c", drive);

	return buffer;
}
