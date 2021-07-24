#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ARGS
	#define OUTPUT_FILE "/media/daniel/disk/FPUPDATE.DAT"
	#define TEMP_FILE "output"
	#define INPUT_FILE "hs20exr.DAT"
	#define ASM_FILE "dump.o"
	#define START_ADDR 0x0040679c
#endif

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

	FILE *f = fopen(INPUT_FILE, "r");
	if (!f) {puts("Bad input file."); return;}
	fread(&header, 1, sizeof(header), f);

	printf("Hardware version: %x\n", header.os);
	printf("Firmware Version: %d.%x\n", header.version1, header.version2);

	printf("Checksum: %x\n", header.checksum);

	unsigned int offset = 0;

	// Payload data is bit flipped
	FILE *o = fopen(TEMP_FILE, "w");
	if (!o) {puts("Bad temp file."); return;}
	while (1) {
		int c = fgetc(f);
		if (c == EOF) {
			break;
		}

		// Main injection code
		if (offset == START_ADDR) {
			// Load up assembly output
			unsigned char inject[1024];
			FILE *a = fopen(ASM_FILE, "r");
			if (!a) {puts("Bad asm file."); return;}
			unsigned int injectLen = fread(inject, 1, 1024, a);

			printf("%u\n", injectLen);
		
			unsigned char temp[injectLen];
			unsigned int checksum1 = 0;
			unsigned int checksum2 = 0;

			for (unsigned int i = 0; i < injectLen; i++) {
				temp[i] = (unsigned char)~c;
				checksum1 += temp[i];
				c = fgetc(f);
				offset++;
			}

			for (unsigned int i = 0; i < injectLen; i++) {
				fputc(inject[i], o);
				checksum2 += inject[i];
			}

			printf("Size: %lx %lx\n", sizeof(inject), sizeof(temp));
			printf("Checksums: %x %x\n", checksum2, checksum1);
		}

		fputc((unsigned char)~c, o);
		offset++;
	}

	fclose(o);
}

void pack() {
	FILE *f = fopen(OUTPUT_FILE, "wr");
	if (!f) {puts("Bad output file."); return;}

	unsigned int checksum1 = 0;
	unsigned int checksum2 = 0;

	// Read the original header
	FILE *p = fopen(INPUT_FILE, "r");
	if (!p) {puts("Bad input file."); return;}
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
	FILE *o = fopen(TEMP_FILE, "r");
	if (!o) {puts("Bad temp file."); return;}
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
	o = fopen(TEMP_FILE, "r");
	if (!o) {puts("Bad temp file."); return;}
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
	if (!strcmp(argv[1], "pack")) {
		pack();
	} else if (!strcmp(argv[1], "unpack")) {
		unpack();
	}

	return 0;
}