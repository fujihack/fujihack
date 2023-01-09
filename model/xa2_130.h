/*
Fujifilm X-A2
Mirrorless
Released March 2015
https://en.wikipedia.org/wiki/Fujifilm_X-A2
*/

#define MODEL_NAME "Fujifilm X-A2"
#define MODEL_CODE "00050701000507020005070400050709"
#define FIRM_URL "https://dl.fujifilm-x.com/support/firmware/x-a2-130-oqijkawt/FWUP0006.DAT"
#define CODE_ARM
#define S3_FILE "C:\\IMFIDX10\\LX30B.S3"

// Dead code (doesn't work in camera, not in manual)
#define FIRM_IMG_PROPS 0x00598aec
#define FIRM_IMG_PROPS_MAX 2000
#define FIRM_RST_WRITE 0x005b0388
#define FIRM_RST_CONFIG1 0x00592bd4
#define FIRM_RST_CONFIG2 0x005b81e0

#define FIRM_PTP_9805 0x008722f8
#define FIRM_PTP_FINISH 0x0087b94c
#define FIRM_PTP_MAX 3000

#ifdef STUBS
	#include "stub.h"
#endif
