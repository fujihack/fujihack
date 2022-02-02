#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// These things are sent in by the Makefile, declare
// them to keep linter happy
#ifndef TEMP_FILE
	#define TEMP_FILE ""
#endif
#ifndef OUTPUT_FILE
	#define OUTPUT_FILE ""
#endif
#ifndef INPUT_FILE
	#define INPUT_FILE ""
#endif
#ifndef MODEL
	#define MODEL ""
#endif
#ifndef ASM_FILE
	#define ASM_FILE "main.S"
#endif
#ifndef MODEL_NAME
	#include "model/hs20exr.h"
#endif

#define ARMCC "arm-none-eabi"

char include[1024];
char command[4096];
char asmflag[1024];

// Standard header for all Fujifilm firmware
struct Header {
	// Some kind of OS/Hardware version
	// Firmware layout version?
	unsigned int os;

	// Proprietary model ID (same across different
	// firmware versions, different for different models)
	// 512 by default, may need to be 128 (On Z3 for example)
	#ifndef MODEL_SIZE
		#define MODEL_SIZE 512
	#endif
	unsigned char model[512];

	// Printed as hex in the camera. X.X
	unsigned int version1;
	unsigned int version2;

	// File checksum
	unsigned int checksum;

	// Generally just 1 (?)
	unsigned int noIdea;
};

void inject(unsigned long addr, char input[], int max) {
	char file[5000];

	// Load up assembly output
	FILE *a = fopen(input, "r");
	if (a == NULL) {printf("[ERR] Can't open %s\n", input); exit(1);}
	unsigned long length = fread(file, 1, sizeof(file), a);
	fclose(a);

	printf("[INFO] Injection size is %lu bytes\n", length);
	if (length > (unsigned long)max) {
		puts("[ERR] assembly output overflows max specified value!");
		exit(1);
	}
	
	FILE *f = fopen(TEMP_FILE, "r+w");
	if (f == NULL) {printf("[ERR] Can't open %s\n", TEMP_FILE); exit(1);}
	fseek(f, addr, SEEK_SET);
	fwrite(file, 1, length, f);
	fclose(f);
}

void unpack() {
	struct Header header;

	FILE *f = fopen(INPUT_FILE, "r");
	if (f == NULL) {printf("[ERR] Can't open %s\n", INPUT_FILE); exit(1);}
	fread(&header, 1, sizeof(header), f);

	printf("[INFO] Hardware version: %x\n", header.os);
	printf("[INFO] Firmware Version: %u.%x\n", header.version1, header.version2);

	printf("[INFO] Checksum: %x\n", header.checksum);

	// Payload data is bit flipped
	FILE *o = fopen(TEMP_FILE, "w");
	if (o == NULL) {printf("[ERR] Can't open %s\n", TEMP_FILE); exit(1);}
	while (1) {
		int c = fgetc(f);
		if (c == EOF) {
			break;
		}

		fputc((unsigned char)~c, o);
	}

	fclose(o);
	fclose(f);
}

void pack() {
	FILE *f = fopen(OUTPUT_FILE, "wr");
	if (f == NULL) {printf("[ERR] Can't open %s\n", OUTPUT_FILE); exit(1);}

	unsigned int checksum1 = 0;
	unsigned int checksum2 = 0;

	// Read the original header
	FILE *p = fopen(INPUT_FILE, "r");
	if (p == NULL) {printf("[ERR] Can't open %s\n", INPUT_FILE); exit(1);}

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
	if (o == NULL) {printf("[ERR] Can't open %s\n", TEMP_FILE); exit(1);}
	while (1) {
		int c = fgetc(o);
		if (c == EOF) {
			break;
		}

		checksum2 += (unsigned char)c;
	}

	fclose(o);

	printf("[INFO] Original checksum: %x\n", checksum1);
	printf("[INFO] New checksum: %x\n", checksum2);

	if (checksum1 < checksum2) {
		header.checksum -= checksum2 - checksum1;
		printf("[INFO] Subtracted %x from checksum.\n", checksum2 - checksum1);
	} else if (checksum1 > checksum2) {
		header.checksum += checksum1 - checksum2;
		printf("[INFO] Added %x to checksum.\n", checksum1 - checksum2);
	}

	// Change firmware version
	header.version2++;

	printf("[INFO] Firmware Version: %d.%d\n", header.version1, header.version2);

	fseek(f, 0, SEEK_SET);
	fwrite(&header, 1, sizeof(header), f);

	// Copy payload from output
	o = fopen(TEMP_FILE, "r");
	if (o == NULL) {printf("[ERR] Can't open %s\n", TEMP_FILE); exit(1);}
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

void run(char string[]) {
	printf("[COMPILING] %s\n", string);
	if (system(string)) {
		puts("Command failed");
		exit(0);
	}
}

void laySection(char block[], unsigned long mem, unsigned long text, unsigned long length) {
	printf("[INFO] Offset: 0x%lx\n", mem - text);
	printf("[INFO] Will copy text: %lx - %lx\n", text, text + length);
	printf("[INFO] To:             %lx - %lx\n", mem, mem + length);

	for (int i = 0; i < (int)length; i++) {
		block[mem + i] = block[text + i];
	}

	// Cover up old spots (to prevent string duplicates)
	for (int i = 0; i < (int)length; i++) {
		block[text + i] = 'A';
	}
}

void lay() {
	// Tried to recreate what would be in memory.
	// I found these addresses by referring to
	// the open-source SQLite code, which is
	// included in the camera. I first matched
	// up code from the firmware and the SQLite
	// repository, and then looked for a string
	// to calculate the offset from.
	
	FILE *f = fopen(TEMP_FILE, "r+w");
	if (f == NULL) {printf("[ERR] Can't open %s\n", TEMP_FILE); exit(1);}

	fseek(f, 0, SEEK_END);
	unsigned long length = ftell(f);
	fseek(f, 0, SEEK_SET);

	char *block = malloc(length);
	fread(block, 1, length, f);

	#ifdef COPY_LENGTH
		laySection(block, MEM_START, TEXT_START, COPY_LENGTH);
	#endif

	// Second data transfer if needed
	#ifdef COPY_LENGTH2
		laySection(block, MEM_START2, TEXT_START2, COPY_LENGTH2);
	#endif

	// Second data transfer if needed
	#ifdef COPY_LENGTH3
		laySection(block, MEM_START3, TEXT_START3, COPY_LENGTH3);
	#endif

	fseek(f, 0, SEEK_SET);
	fwrite(block, 1, length, f);
	fclose(f);
	
	free(block);
}

int main(int argc, char *argv[]) {
	if (argc <= 1) {
		return 1;
	}

	sprintf(
		command,
		"touch %s %s",
		TEMP_FILE, OUTPUT_FILE
	); run(command);

	if (!strcmp(argv[1], "pack")) {
		pack();
	} else if (!strcmp(argv[1], "unpack")) {
		unpack();
	} else if (!strcmp(argv[1], "lay")) {
		unpack();
		lay();
	} else if (!strcmp(argv[1], "inject")) {
		if (argc < 5) {
			printf("[ERR] Not enough parameters for 'inject'\n");
			return 1;
		}

		int address = strtol(argv[3], (char **)NULL, 0);
		int max = strtol(argv[4], (char **)NULL, 0);

		printf("[INFO] Writing '%s' at %x, (%d)\n", argv[2], address, max);

		inject(address, argv[2], max);
	}

	return 0;
}
