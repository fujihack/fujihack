#include <stdio.h>
#include <stdlib.h>

#define COMMON_DUMP 0x0990cfcd
#define COMMON_FIRM 0x00423f55

int main() {
	FILE *a = fopen("/home/daniel/Documents/fujihack/output", "r");
	FILE *b = fopen("/home/daniel/Documents/dump/RAM.BIN", "r");

	long i = 0;

	while (1) {
		fseek(a, COMMON_FIRM - i, SEEK_SET);
		fseek(b, COMMON_DUMP - i, SEEK_SET);
		printf("Down %lu\n", i);
		if (fgetc(a) != fgetc(b)) {
			printf("Broke at %lx %lx\n", ftell(a), ftell(b));
			return 0;
		}

		i++;
	}

	return 0;
}
