#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "fujifilm.h"
#include "rst.h"

#include "fujihack.h"
#include "sqlite.h"
#include "screen.h"
#include "hijack.h"

// Main entry file, nothing much to see.

void entry() {

	// Print custom text to PTP/USB "VendorExtensionDesc"
	strcpy((char*)MEM_PTP_TEXT, "Hello, World");

	// Dump 256mb RAM
	//memory_dump("X:\\RAM.BIN", 0x0);
}
