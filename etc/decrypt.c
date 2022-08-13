// Include a model file
#include "../model/xf1_101.h"
#define DUMP_FILE "/home/daniel/Documents/dump/RAM.BIN"
#define SIZE 0x1000000

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
	FILE *f = fopen(DUMP_FILE, "r");

	fseek(f, MEM_FIRM_START, SEEK_SET);
	uint8_t *firm = malloc(SIZE);
	fread(firm, SIZE, 1, f);

	fseek(f, MEM_CRYPT_START, SEEK_SET);
	uint8_t *crypt = malloc(SIZE);
	fread(crypt, SIZE, 1, f);

	fclose(f);

	f = fopen("firm.o", "w");
	fwrite(firm, SIZE, 1, f);
	fclose(f);

	f = fopen("crypt.o", "w");
	fwrite(crypt, SIZE, 1, f);
	fclose(f);

	return 0;
}
