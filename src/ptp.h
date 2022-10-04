#ifndef PTP_H
#define PTP_H

#include <stdint.h>

struct FujiPTPParams {
	uint32_t code; // ptp command code
	uint32_t transid; // ?
	uint32_t sessionid; // ?
	uint32_t length; // ?
	uint32_t param1;
	uint32_t param2;
};

struct FujiPTPResponse {
	uint32_t code;
	uint32_t transid;
	uint32_t sessionid;
	uint32_t nparam;
	uint32_t param1;
	uint32_t param2;
	uint32_t param3;
};

struct FujiPTPData {
	uint32_t a;
	// ?????
};

// Function for each PTP opcode handler
void fuji_ptp_function(uint8_t mode, struct FujiPTPParams *params, struct FujiPTPData *data);

// "x" is generally 0
void fuji_ptp_finish(struct FujiPTPParams *params, int retcode, int retcode2);
void fuji_ptp_return(int retcode, int x);

#endif
