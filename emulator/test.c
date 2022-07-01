#include <stdint.h>

#include <sqlite.h>
#include <fujifilm.h>

char buffer[100];

char *_start() {

	int *asd = 0;
	sqlite_snprintf(100, buffer, "Test: %d", random_test3(2));

	return buffer;
}
