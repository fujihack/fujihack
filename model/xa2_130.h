/*
Fujifilm X-A2
Mirrorless
Released March 2015
https://en.wikipedia.org/wiki/Fujifilm_X-A2
*/

#define MODEL_NAME "Fujifilm X-A2"
#define MODEL_CODE "00050701000507020005070400050709"

#define NO_THUMB

#define S3_FILE "C:\\IMFIDX10\\LX30B.S3"

#ifdef STUBS
	#include "stub.h"

	NSTUB(show_photo_properties, 0x01553b1b)
#endif
