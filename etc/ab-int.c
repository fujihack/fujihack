#include <stdio.h>
#include <stdint.h>

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

int main() {
	char b[32] = "AAAAAAAA";
	generate(0x12345678, b);
	printf("Text: %s\n", b);
	printf("int: %X\n", read(b));
}
