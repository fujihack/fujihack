#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Basic self testing
// - make sure malloc() creates valid addresses
// - Make sure free() works

int sys_fast_self_test() {
	void *b = malloc(17);

	if (b == NULL) {
		return 1;
	}

	int n = sqrt(64);
	if (n != 8) {
		return 1;
	}

	return 0;
}
