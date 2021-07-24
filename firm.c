#include <stdio.h>
#include <stdlib.h>

char *outputFile = "/media/daniel/disk/FPUPDATE.DAT";
char *tempFile = "output";
char *inputFile = "hs20exr.DAT";

unsigned int start = 0x01008094;
unsigned char inject[] = {
	'H', 0,
	'A', 0,
	'C', 0,
	'K', 0,
	'E', 0,
	'D', 0,
	' ', 0,
	'B', 0,
	'Y', 0,
	' ', 0,
	'D', 0,
	'A', 0,
	'N', 0,
	0, 0, 0, 0, 0
};

struct Header {
	// Some kind of OS/Hardware version
	unsigned int os;

	// Proprietary model ID (same across different
	// firmware versions, different for different models)
	unsigned char model[512];
	// Printed as hex in the camera. X.X
	unsigned int version1;
	unsigned int version2;

	// File checksum, may have an offset
	unsigned int checksum;

	// ???
	unsigned int noIdea;
};

void unpack() {
	struct Header header;

	FILE *f = fopen(inputFile, "r");
	fread(&header, 1, sizeof(header), f);

	printf("Hardware version: %x\n", header.os);
	printf("Firmware Version: %d.%x\n", header.version1, header.version2);

	printf("Checksum: %x\n", header.checksum);

	unsigned int offset = 0;

	// Payload data is bit flipped
	FILE *o = fopen(tempFile, "w");
	while (1) {
		int c = fgetc(f);
		if (c == EOF) {
			break;
		}

#if 1
		if (offset == start) {
			unsigned char temp[sizeof(inject)];

			unsigned int checksum1 = 0;
			unsigned int checksum2 = 0;

			for (unsigned int i = 0; i < sizeof(inject); i++) {
				temp[i] = (unsigned char)~c;
				checksum1 += temp[i];
				c = fgetc(f);
				offset++;
			}

			for (unsigned int i = 0; i < sizeof(inject); i++) {
				fputc(inject[i], o);
				checksum2 += inject[i];
			}

			printf("Size: %lx %lx\n", sizeof(inject), sizeof(temp));
			printf("Checksums: %x %x\n", checksum2, checksum1);

#if 0
			// Write the bytes in reverse
			unsigned int i = end - start - 1;
			while (1) {
				fputc(temp[i], o);
				if (i == 0) {
					break;
				}

				i--;
			}
#endif
		}
#endif
		fputc((unsigned char)~c, o);
		offset++;
	}

	fclose(o);
}

void pack() {
	FILE *f = fopen(outputFile, "wr");

	unsigned int checksum1 = 0;
	unsigned int checksum2 = 0;

	// Read the original header
	FILE *p = fopen(inputFile, "r");
	struct Header header;
	fread(&header, 1, sizeof(header), p);

	// Get original file checksum
	while (1) {
		int c = fgetc(p);
		if (c == EOF) {
			break;
		}

		checksum1 += (unsigned char)~c;
	}

	fclose(p);

	// Get modified file checksum
	FILE *o = fopen(tempFile, "r");
	while (1) {
		int c = fgetc(o);
		if (c == EOF) {
			break;
		}

		checksum2 += (unsigned char)c;
	}

	fclose(o);

	printf("Original checksum: %x\n", checksum1);
	printf("New checksum: %x\n", checksum2);

	if (checksum1 < checksum2) {
		header.checksum -= checksum2 - checksum1;
		printf("Subtracted %x from checksum.\n", checksum2 - checksum1);
	} else if (checksum1 > checksum2) {
		header.checksum += checksum1 - checksum2;
		printf("Added %x to checksum.\n", checksum1 - checksum2);
	}

	// Change firmware version
	header.version2++;

	printf("Firmware Version: %d.%d\n", header.version1, header.version2);

	fseek(f, 0, SEEK_SET);
	fwrite(&header, 1, sizeof(header), f);

	// Copy payload from output
	o = fopen(tempFile, "r");
	while (1) {
		int c = fgetc(o);
		if (c == EOF) {
			break;
		}
		
		fputc((unsigned char)~c, f);
	}

	fclose(o);
	fclose(f);
}

int main(int argc, char *argv[]) {
	argc = argc;
	switch (argv[1][0]) {
		case 'p':
			pack();
			break;
		case 'u':
			unpack();
			break;
	}

	return 0;
}
