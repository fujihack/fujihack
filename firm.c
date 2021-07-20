#include <stdio.h>
#include <stdlib.h>

char *original = "FWUP0024.DAT";

// Length of header (before xored payload)
#define HEADERLEN 4 + 512 + 16

void unpack() {
	// System software version, relates
	// to camera model
	unsigned int version;

	// Some kind of checksum (?) AES IV?
	unsigned char key[512] = {0};

	// Firmware version and initial information
	unsigned char firmver[16] = {0};

	FILE *f = fopen(original, "r");
	fread(&version, 1, 4, f);
	fread(key, 1, 512, f);
	fread(firmver, 1, 16, f);

	// Payload data is bit flipped
	FILE *o = fopen("output", "w");
	while (1) {
		int c = fgetc(f);
		if (c == EOF) {
			break;
		}

		fputc(~(unsigned char)c, o);
	}

	fclose(o);
}

// Firmware numbers are printed in hex.
#define HEADER_V1 4 + 512
#define HEADER_V2 4 + 512 + 4

void pack() {
	FILE *f = fopen("FPUPDATE.DAT", "wr");

	// Write the original header
	FILE *p = fopen(original, "r");
	char header[HEADERLEN];
	fread(header, 1, HEADERLEN, p);
	fclose(p);

	printf("Firmware Version: %d.%d\n", header[4 + 512], header[4 + 512 + 4]);

	// Change firmware version
	//header[4 + 512] = 1;
	//header[4 + 512 + 4] = 5;

	fseek(f, 0, SEEK_SET);
	fwrite(header, 1, HEADERLEN, f);

	// Copy payload from output
	FILE *o = fopen("output", "r");

	while (1) {
		int c = fgetc(o);
		if (c == EOF) {
			break;
		}
		
		fputc(~(unsigned char)c, f);
	}

	fclose(f);
	fclose(o);
	
}

int main(int argc, char *argv[]) {
	switch (argv[1][0]) {
		case 'p':
			pack();
			break;
		case 'u':
			unpack();
			break;
	}
}