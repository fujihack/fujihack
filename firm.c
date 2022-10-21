// This file is deprecated, but left as a reference
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// CLI Default values
struct cli {
	char *temp;
	char *output;
	char *input;
	char *model;
	char *max;
	char *addr;
	char *inject;
}Cli = {
	.temp = "output",
	.output = "FPUPDATE.DAT",
	.input = "FPUPDATE-xf1.DAT",
	.model = "xf1_101",
	.max = NULL,
	.addr = NULL,
	.inject = "inject.o"
};

// Bypass linter
#ifndef MODEL_NAME
	#include "model/template.h"
#endif

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
	unsigned char code[MODEL_SIZE];

	// Printed as hex in the camera. X.X
	unsigned int version1;
	unsigned int version2;

	// File checksum
	unsigned int checksum;

	// Generally just 1 (?)
	unsigned int end;
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
	
	FILE *f = fopen(Cli.temp, "r+w");
	if (f == NULL) {printf("[ERR] Can't open %s\n", Cli.temp); exit(1);}
	fseek(f, addr, SEEK_SET);
	fwrite(file, 1, length, f);
	fclose(f);
}

// Parse the 512 byte model ID in the firmware header
// (Sometimes 128, sometimes 1024 (?))
// This is a basic dump, further analysis: https://docs.google.com/spreadsheets/d/1HnRGIC9CDXgBGscjW5mOb_aKOIqzI9wp8RbXZ-fu78k/edit#gid=396646525
void parseCode(unsigned char *code) {
	int x = 0;

	char parseCode[MODEL_SIZE / 2 + 1];

	for (int i = 1; i < MODEL_SIZE; i += 2) {
		parseCode[x] = code[i];
		x++;
	}

	// Trim off trailing zeros
	x--;
	while (parseCode[x] == '0') {
		x--;
	}
	x++;

	parseCode[x] = '\0';

	printf("[INFO] Model Code:  %s\n", parseCode);

	#ifdef MODEL_CODE
		if (strcmp(MODEL_CODE, parseCode)) {
			puts("[ERR] Model code didn't match code stored in the header file.");
			exit(1);
		}
	#endif
}

void unpack() {
	struct Header header;

	FILE *f = fopen(Cli.input, "r");
	if (f == NULL) {printf("[ERR] Can't open %s\n", Cli.input); exit(1);}
	fread(&header, 1, sizeof(header), f);

	parseCode(header.code);

	// Generate model code from header, Eg "101" from 1.01
	char verCode[8];
	if (header.version2 >= 0x10) {
		snprintf(verCode, 8, "%x%x", header.version1, header.version2);
	} else {
		snprintf(verCode, 8, "%x0%x", header.version1, header.version2);
	}

	int i;
	for (i = 0; Cli.model[i] != '_'; i++) {
		if (Cli.model[i] == '\0') {
			puts("[WARN] Model name doesn't include version.");
			goto skip;
		}
	}
	i++;

	if (strcmp(Cli.model + i, verCode)) {
		printf("[ERR] Firmware does not match chosen model.\n");
		exit(1);
	}

	skip:;

	printf("[INFO] Hardware version: %x\n", header.os);
	printf("[INFO] Firmware Version: %s\n", verCode);

	printf("[INFO] Checksum: %x\n", header.checksum);

	// Payload data is bit flipped
	FILE *o = fopen(Cli.temp, "w");
	if (o == NULL) {printf("[ERR] Can't open %s\n", Cli.temp); exit(1);}
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
	FILE *f = fopen(Cli.output, "wr");
	if (f == NULL) {printf("[ERR] Can't open %s\n", Cli.output); exit(1);}

	unsigned int checksum1 = 0;
	unsigned int checksum2 = 0;

	// Read the original header
	FILE *p = fopen(Cli.input, "r");
	if (p == NULL) {printf("[ERR] Can't open %s\n", Cli.input); exit(1);}

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
	FILE *o = fopen(Cli.temp, "r");
	if (o == NULL) {printf("[ERR] Can't open %s\n", Cli.temp); exit(1);}
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

	printf("[INFO] New header checksum: %x\n", header.checksum);

	// Change firmware version
	header.version2++;

	printf("[INFO] Firmware Version: %d.%d\n", header.version1, header.version2);

	fseek(f, 0, SEEK_SET);
	fwrite(&header, 1, sizeof(header), f);

	// Copy payload from output
	o = fopen(Cli.temp, "r");
	if (o == NULL) {printf("[ERR] Can't open %s\n", Cli.temp); exit(1);}
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
	
	FILE *f = fopen(Cli.temp, "r+w");
	if (f == NULL) {printf("[ERR] Can't open %s\n", Cli.temp); exit(1);}

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

	// Third data transfer if needed
	#ifdef COPY_LENGTH3
		laySection(block, MEM_START3, TEXT_START3, COPY_LENGTH3);
	#endif

	fseek(f, 0, SEEK_SET);
	fwrite(block, 1, length, f);
	fclose(f);
	
	free(block);
}

void help() {
	printf(
		"FujiHack firmware utility\n"
		"Utility compiled for %s.\n"
		"Licesed under the GNU General Public License v3.0\n"
		"https://github.com/petabyt/fujifilm\n"
		"Options:\n"
		"\t-t\t Temporary file\n"
		"\t-o\t Output file\n"
		"\t-i\t Input file\n"
		"\t-m\t Model name\n"
		"\t-a\t Injection address\n"
		"\t-j\t Injection input file\n"
		"\t-x\t Max injection input file size\n",
		MODEL_NAME
	);
}

int main(int argc, char *argv[]) {
	char *action = "none";

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
			case 'h':
				help();
				return 0;
			case 't':
				Cli.temp = argv[i + 1]; i++;
				break;
			case 'o':
				Cli.output = argv[i + 1]; i++;
				break;
			case 'i':
				Cli.input = argv[i + 1]; i++;
				break;
			case 'm':
				Cli.model = argv[i + 1]; i++;
				break;
			case 'a':
				Cli.addr = argv[i + 1]; i++;
				break;
			case 'x':
				Cli.max = argv[i + 1]; i++;
				break;
			case 'j':
				Cli.inject = argv[i + 1]; i++;
				break;
			default:
				printf("[ERR] Unknown option %c\n", argv[i][1]);
				return 1;
			}
		} else {
			action = argv[i];
		}
	}

	if (argc <= 4) {
		help();
		return 0;
	}

	#ifdef MODEL
		if (strcmp(Cli.model, MODEL)) {
			puts("[ERR] firm.c wasn't compiled with the right module. You need to recompile.");
			return 1;
		}
	#endif

	if (!strcmp(action, "pack")) {
		pack();
	} else if (!strcmp(action, "unpack")) {
		unpack();
	} else if (!strcmp(action, "lay")) {
		unpack();
		lay();
	} else if (!strcmp(action, "inject")) {
		if (Cli.addr == NULL || Cli.max == NULL || Cli.inject == NULL) {
			puts("[ERR] Parameters not defined for inject");
			return 1;
		}

		int address = strtol(Cli.addr, (char **)NULL, 0);
		int max = strtol(Cli.max, (char **)NULL, 0);

		printf("[INFO] Writing '%s' at %x, (%d)\n", Cli.inject, address, max);

		inject(address, Cli.inject, max);
	} else {
		puts("[ERR] Unknown action.");
		return 1;
	}

	return 0;
}
