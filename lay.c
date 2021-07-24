#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tried to recreate what would be in memory.
// I found these addresses by referring to
// the open-source SQLite code, which is
// included in the camera. I first matched
// up code from the firmware and the SQLite
// repository, and then looked for a string
// to calculate the offset from.

int main() {
	FILE *f = fopen("output", "r+w");

	char *block = malloc(33850236 + 100);
	fread(block, 1, 33850236, f);

	for (int i = 0; i < 1000000; i++) {
		block[0x00db6568 - 10000 + i] = block[0x0074e5b0 - 10000 + i];
	}

	fseek(f, 0, SEEK_SET);
	fwrite(block, 1, 33850236, f);
	fclose(f);
}
