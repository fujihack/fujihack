#include <stdint.h>

#include <sqlite.h>
#include <hijack.h>
#include <fujifilm.h>

char buffer[32];

// Log to string custom IO
void iolog(char *string) {
	uint8_t *io = (uint8_t*)0x10000000;
	while (*string != '\0') {
		io[0] = *string;
		string++;
	}

	io[0] = '\0';
}

void *entry() {
	foo_bar();
	return 0;
}

