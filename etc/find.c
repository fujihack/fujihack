#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *b = fopen("/home/daniel/Documents/dump/RAM.BIN", "r");

#if 0
	long i = 0;

	char str[] = "Dump";

	char buf[64];

	top:;
	//printf("%u\n", (int)i);
	if (fseek(b, i, SEEK_SET)) {
		return 1;
	}

	i++;

	fread(buf, 10, 1, b);
	for (int i = 0; i < (int)sizeof(str); i++) {
		if (str[i] != buf[i * 2]) {
			goto top;
		}
	}

	printf("%u\n", (int)i);
#endif

	char buf[32];
	uint32_t id = 0;
	fseek(b, 0x00fd5ee8, SEEK_SET);
	for (int i = 0; i < 114; i++) {
		fread(buf, 1, 0x10 - 4, b);
		fread((void*)&id, 1, 4, b);
		printf("| %u | %s | ... |\n", id, buf);
	}
	
	
	return 0;
}
