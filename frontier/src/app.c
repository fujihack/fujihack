// Basic code to detect and load apps
// Copyright (C) 2022-2023 Frontier by Daniel C - Apache License
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#include <sys.h>
#include <elf.h>
#include <app.h>
#include <loader.h>

void *alloc_elf_file(char *filename, int *length) {
	FILE *f = fopen(filename, "rb");
	if (f == NULL) {
		sys_debug("Failed to open file\n");
		return NULL;
	}

	struct stat s;
	if (stat(filename, &s)) {
		sys_debug("stat() err\n");
		return NULL;
	}
	*length = s.st_size;

	sys_debug("File size: %lu\n", s.st_size);

	void *buffer = malloc(s.st_size);
	if (buffer == NULL) {
		sys_debug("Failed to allocate ELF buffer\n");
		return NULL;
	}

	size_t x = fread(buffer, 1, 64, f);

	// TODO: DO header figuring here...
	
	x += fread(buffer + 64, 1, s.st_size - 64, f);
	if (x != s.st_size) {
		sys_debug("Coundn't read file\n");
		return 0;
	}

	fclose(f);

	return buffer;
}

// Quickly read a few bytes of an app, and get icon, name, any info, etc.
int app_get_info(char *filename, struct AppMetaData *data) {
	FILE *f = fopen(filename, "rb");
	if (f == NULL) {
		return -1;
	}

	char tmp[128];
	fread(tmp, 1, sizeof(tmp), f);

	fclose(f);

	struct AppMetaData *md = (struct AppMetaData *)tmp;
	if (md->magic1 == 'F' && md->magic2 == 'R') {
		//return parse_app_metadata(f);
	}

	uint32_t *chk32 = (uint32_t *)tmp;
	if (chk32[0] == ELF_MAGIC) {
		//return load_app_elf(f);
	}

	return -2;
}

int sys_load_app(char *filename) {
	int length = 0;
	void *buffer = alloc_elf_file(filename, &length);
	if (buffer == NULL) {
		sys_report_err("File allocation error");
		return 1;
	}

	if (buffer == NULL) return 1;

	struct ElfFileInfo i;

	int ret = loader_init_elf(buffer, &i);
	if (ret) {
		printf(sys_get_error());
		return 1;
	}

	loader_scan_symbols(buffer, &i);

	if (!ret) {
		sys_debug("Returned: %lX\n", loader_exec(buffer, &i));
	}

	return 0;
}
