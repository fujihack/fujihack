#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODEL "hs20exr"
#define ARMCC "arm-none-eabi"

//#define OUTPUT_FILE "FPUPDATE.DAT"
#define OUTPUT_FILE "/media/daniel/disk/FPUPDATE.DAT"
#define INPUT_FILE "../fujifilm/hs20exr.DAT"
#define TEMP_FILE "output"

char include[1024];
char asmflag[1024];
char command[2048];

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

void run(char string[]) {
	//printf("______ %s\n", string);
	if (system(string)) {
		exit(0);
	}
}

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
	printf("Firmware Version: %d.%x\n", header.version1, header.version2);

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
	puts("HS20EXR ONLY");
	
	// Tried to recreate what would be in memory.
	// I found these addresses by referring to
	// the open-source SQLite code, which is
	// included in the camera. I first matched
	// up code from the firmware and the SQLite
	// repository, and then looked for a string
	// to calculate the offset from.
	
	FILE *f = fopen("output", "r+w");

	char *block = malloc(33850236 + 100);
	fread(block, 1, 33850236, f);

	for (int i = 0; i < 1000000; i++) {
		block[0x00db6568 - 10000 + i] = block[0x0074e5b0 - 10000 + i];
	}

	fseek(f, 0, SEEK_SET);
	fwrite(block, 1, 33850236, f);
	fclose(f);
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
		lay();
	} else if (!strcmp(argv[1], "asm")) {
		unpack();
		injectAssembly("dump.S", 0x0040674c);
		injectAssembly("usb.S", 0x00386a10);
		pack();
	}

	run("rm -rf *.o *.out *.elf output *.DAT");

	return 0;
}