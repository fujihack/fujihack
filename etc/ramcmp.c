#include <stdio.h>
#include <stdlib.h>

#include "../model/xf1_101.h"

int main() {
	FILE *a = fopen("/home/daniel/Documents/dump/sec/RAM1.BIN", "r");
	FILE *b = fopen("/home/daniel/Documents/dump/sec/RAM2.BIN", "r");
	if (b == NULL || a == NULL) {
		puts("Err");
		return 1;
	}

	fseek(a, 0, SEEK_SET);
	fseek(b, 0, SEEK_SET);

	uint32_t aa = 0;
	uint32_t bb = 0;

	for (int i = 0; i < 0x10000000 / 4; i += 4) {
		fread(&aa, 4, 1, a);
		fread(&bb, 4, 1, b);
		if (aa < bb) {
			if (bb - aa > 1000 * 35) continue;
			if (bb - aa < 1200) continue;
			printf("Diff at 0x%x, %u\n", i, bb - aa);
		}
	}

	puts("No diff");

	return 0;
}
