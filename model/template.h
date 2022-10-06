/*
Fujifilm X-TEMPLATE

*/

#define MODEL_NAME "Fujifilm XXXXX"
#define MODEL_CODE "Paste_model_code_from_patcher"

// Uses ARM 32 bit (not thumb) byte code in firmware
#define CODE_ARM

#ifdef STUBS
	#include "stub.h"
	NSTUB(FUN_0x1234567, 0x123456)
#endif
