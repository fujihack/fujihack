#ifndef PACK_H
#define PACK_H

#include <stdint.h>

#pragma pack(push, 1)

struct AppMetaData {
	uint32_t api_version;
	uint32_t header_size;
	char name[20];
	char author[20];
	char url[40];
	uint8_t icon[];
};

struct TblEntry {
	uint32_t addr;
	uint16_t length;
	uint8_t type;
	uint8_t etc;
	char string[];
};

#pragma pack(pop)

int add_syms(char *input, char *output);
int gen_app_meta(struct AppMetaData *amd, char *content);
#endif
