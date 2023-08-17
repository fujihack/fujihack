// movie mode hacks
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <ff_io.h>

static int record_limit() {
	// 666 minutes
	return 60 * 60 * 666;
}

int fh_infinite_record_limit() {
	uint32_t inst[] = {
		0xe28f0004, // adr r0, x
		0xe5900000, // ldr r0, [r0]
		0xe12fff10, // bx r0
		(uint32_t)record_limit,
	};

	memcpy((void *)MEM_GET_REC_LIMIT, inst, sizeof(inst));	
}
