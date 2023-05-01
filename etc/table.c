#include <stdio.h>
#include <stdint.h>
#include <string.h>
// Text table finder

#define DUMP_FILE "/home/daniel/Downloads/xa2-RAM.BIN"

#define TEXT_TABLE 0x0039f70c

char buffer[512];

int test_text(FILE *f) {
	long int p = ftell(f);

	fseek(f, p + 4, SEEK_SET);

	uint32_t address = 0;
	fread(&address, 1, 4, f);

	if (address == 0) {
		goto l1;
	}

	if (fseek(f, address, SEEK_SET)) {
		return 1;
	}

	fread(&address, 1, 4, f);

	if (address > 0x10000000) {
		return 1;
	}

	if (address == 0) {
		goto l1;
	}

	if (fseek(f, address, SEEK_SET)) {
		return 1;
	}

	int i = 0;
	while (1) {
		int c = fgetc(f);
		int c2 = fgetc(f);

		if (c2 == 0 || c2 == 0xe1) {
			buffer[i] = (char)c;
			i++;
		}

		if ((char)c == '\0' || i > 128) {
			break;
		}
	}
	buffer[i] = '\0';

	if (i != 0) {
		puts(buffer);
	}

	l1:
	fseek(f, p + 8, SEEK_SET);
	return 0;
}

int main() {
	FILE *f = fopen(DUMP_FILE, "rb");

	fseek(f, TEXT_TABLE, SEEK_SET);

	// test_text(f);
	// test_text(f);
	// test_text(f);
	// test_text(f);
	// test_text(f);

	int i = 0;
	while (1) {
		int rc = test_text(f);
		if (rc) {
			break;
		}

		char *cmp = "FILM SIMULATION";
		
		if (!strncmp(buffer, cmp, strlen(cmp) + 1)) {
			uint32_t id = 0xff000000 | i;
			printf("Found @ %08X or %X\n", id, i);
			return 0;
		}
		
		if (i > 3000) {
			return 0;
		}
		i++;
	}
}
