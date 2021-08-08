#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MODEL_NAME
	#include "hs20exr.h"
#endif

#define ARMCC "arm-none-eabi"

#ifndef OUTPUT_FILE
	#define OUTPUT_FILE "/media/daniel/disk/FPUPDATE.DAT"
#endif
#ifndef INPUT_FILE
	#define INPUT_FILE "../fujifilm/hs20exr.DAT"
#endif
#define TEMP_FILE "output"

char include[1024];
char asmflag[1024];
char command[4096];

struct Header {
	// Some kind of OS/Hardware version
	// Firmware layout version?
	unsigned int os;

	// Proprietary model ID (same across different
	// firmware versions, different for different models)
	// On older models (Z3), this is 128 bytes long. (?)
	unsigned char model[512];

	// Printed as hex in the camera. X.X
	unsigned int version1;
	unsigned int version2;

	// File checksum
	unsigned int checksum;

	// Generally just 1 (?)
	unsigned int noIdea;
};

void inject(unsigned long addr, char input[]) {
	char file[5000];

	// Load up assembly output
	FILE *a = fopen(input, "r");
	if (!a) {puts("Bad inject file."); return;}
	unsigned long length = fread(file, 1, sizeof(file), a);
	fclose(a);
	
	FILE *f = fopen(TEMP_FILE, "r+w");
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

void injectAssembly(char file[], unsigned long location) {
	sprintf(include, "--include \"%s.h\"", MODEL);
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

	inject(location, "inject.o");
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

	printf("Offset: 0x%x\n", MEM_START - TEXT_START);
	printf("Will copy text: %x - %x\n", TEXT_START, TEXT_START + COPY_LENGTH);
	printf("To:             %x - %x\n", MEM_START, MEM_START + COPY_LENGTH);

	printf("%lu\n", length);

	char *block = malloc(length);
	fread(block, 1, length, f);

	for (int i = 0; i < COPY_LENGTH; i++) {
		block[MEM_START + i] = block[TEXT_START + i];
	}

	// Cover up old spots (to prevent string duplicates)
	for (int i = 0; i < COPY_LENGTH; i++) {
		block[TEXT_START + i] = 'A';
	}

	// Second data transfer if needed
	#ifdef COPY_LENGTH2
		puts("Doing a second copy.");
		printf("Offset: 0x%x\n", MEM_START2 - TEXT_START2);
		printf("Will copy text: %x - %x\n", TEXT_START2, TEXT_START2 + COPY_LENGTH2);
		printf("To:             %x - %x\n", MEM_START2, MEM_START2 + COPY_LENGTH2);
	
		for (int i = 0; i < COPY_LENGTH2; i++) {
			block[MEM_START2 + i] = block[TEXT_START2 + i];
		}
	
		// Cover up old spots (to prevent string duplicates)
		for (int i = 0; i < COPY_LENGTH2; i++) {
			block[TEXT_START2 + i] = 'A';
		}
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
		// Customize to your liking.
		unpack();
		injectAssembly("dump.S", 0x0040674c);
		pack();
	}

	run("rm -rf *.o *.out *.elf *.DAT");

	return 0;
}
