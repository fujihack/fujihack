#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MODEL_NAME
	#include "model/hs20exr.h"
#endif

#define ARMCC "arm-none-eabi"

#define TEMP_FILE "output"

char include[1024];
char asmflag[1024];
char command[4096];

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
	if (!a) {puts("Bad inject file."); return;}
	unsigned long length = fread(file, 1, sizeof(file), a);
	fclose(a);

	puts(INPUT_FILE);

	printf("Size: %lu\n", length);
	if (length > (unsigned long)max) {
		puts("ASSEMBLY OUTPUT OVERFLOWS MAXIMUM SPECIFIED OUTPUT!");
		exit(1);
	}
	
	FILE *f = fopen(TEMP_FILE, "r+w");
	if (!f) {puts("Bad temp file"); exit(1);}
	fseek(f, addr, SEEK_SET);
	fwrite(file, 1, length, f);
	fclose(f);
}

void unpack() {
	struct Header header;

	FILE *f = fopen(INPUT_FILE, "r");
	if (!f) {puts("Bad input file."); return;}
	fread(&header, 1, sizeof(header), f);

	printf("Hardware version: %x\n", header.os);
	printf("Firmware Version: %u.%x\n", header.version1, header.version2);

	printf("Checksum: %x\n", header.checksum);

	// Payload data is bit flipped
	FILE *o = fopen(TEMP_FILE, "w");
	if (!o) {puts("Bad temp file."); return;}
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

void run(char string[]) {
	if (system(string)) {
		exit(0);
	}
}

void injectAssembly(char file[], unsigned long location, int max) {
	sprintf(include, "--include \"model/%s.h\"", MODEL);
	strcpy(asmflag, "-c -marm");

	sprintf(
		command,
		"%s-gcc %s %s -o inject.o %s",
		ARMCC, asmflag, include, file
	); run(command);
	sprintf(
		command,
		"%s-ld -Bstatic inject.o -Ttext 0x%lx -o inject.elf",
		ARMCC, location
	); run(command);
	sprintf(
		command,
		"%s-objcopy -O binary inject.elf inject.o",
		ARMCC
	); run(command);

	run("hexdump -C inject.o");

	inject(location, "inject.o", max);
}

void laySection(char block[], unsigned long mem, unsigned long text, unsigned long length) {
	printf("Offset: 0x%lx\n", mem - text);
	printf("Will copy text: %lx - %lx\n", text, text + length);
	printf("To:             %lx - %lx\n", mem, mem + length);

	for (int i = 0; i < length; i++) {
		block[mem + i] = block[text + i];
	}

	// Cover up old spots (to prevent string duplicates)
	for (int i = 0; i < length; i++) {
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
	if (!f) {
		puts("Could not open temp file.");
		return;
	}

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
	argc = argc;

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
	} else if (!strcmp(argv[1], "asm")) {
		puts("DANGER! Writing code to the firmware!");
		unpack();
		injectAssembly("main.S", FIRMWARE_PRINTIM, 236);
		pack();
	}

	return 0;
}
