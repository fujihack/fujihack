#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void generate(int x, char *buffer) {
	int c = 0;
	for (int i = 0; i < 4; i++) {
		char a = 'A';
		char b = 'A';
		uint8_t t = ((uint8_t*)&x)[i];
		while (t) {
			if (b == 'Z') {
				b = 'A';
				a++;
			}

			b++;
			t--;
		}

		buffer[c] = a;
		buffer[c + 1] = b;

		c += 2;
	}

	buffer[c] = '\0';	
}

int read(char *buffer) {
	uint32_t x = 0;
	uint8_t *t = (uint8_t*)&x;
	int c = 0;
	for (int i = 0; i < 4; i++) {
		char a = buffer[c];
		char b = buffer[c + 1];
		while (a != 'A' || b != 'A') {			
			if (b == 'A') {
				b = 'Z';
				a--;
			}

			b--;
			t[i]++;
		}
		
		c += 2;
	}

	return x;
}

int main(int argc, char *argv[]) {
	if (argv[1][0] != '-') {
		puts("-h for info");
		return 1;
	}

	switch (argv[1][1]) {
	case 't':
		{
			char b[32] = "AAAAAAAA";
			int i;
			for (i = 0; i < 123456; i++) {
				generate(i, b);
				if (read(b) != i) {
					puts("Failed test");
					return 1;
				}
			}
			printf("Passed 0x%X tests\n", i);
		}
		break;
	case 'd':
		printf("Decoded: %08X/%u\n", read(argv[2]), read(argv[2]));
		break;
	case 'g':
		{
		char buffer[16];
		generate(atoi(argv[2]), buffer);
		printf("Generate: %s\n", buffer);
		}
	}
	return 0;
}
