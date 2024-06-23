// Frontier app standard
#ifndef APP_H
#define APP_H
#pragma pack(push, 1)

#include <stdint.h>

enum AppInfoType {
	SYS_APP_FRONTIER,
	SYS_APP_ELF,
};

struct AppInfo {
	//enum AppInfoType;
};

// Frontier official app header structure
struct AppMetaData {
	uint8_t magic1;
	uint8_t magic2;
	uint32_t api_version;
	uint32_t header_size;
	char name[20];
	char author[20];
	char url[40];
	uint8_t icon[];
	// ELF data will follow
};

#pragma pack(pop)
#endif
