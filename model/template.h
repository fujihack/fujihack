/*
Fujifilm X-TEMPLATE

*/

#define MODEL_NAME "Fujifilm XXXXX"

// Paste number from firm utility
#define MODEL_CODE "XXXX"

// Where code thinks the data should be:
#define MEM_START 0x1f54c3c - 10000

// Where the data actually is:
#define TEXT_START 0xbf4c84 - 10000

// How much data should be copied
#define COPY_LENGTH 10000 + 6052

// Function addresses in memory
#ifdef STUBS
	#include "stub.h"

	NSTUB(sqlite_snprintf, 0x123456)
#endif