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

#define FUJI_FOPEN_HANDLER 0x00ea9708
#define FUJI_FWRITE_HANDLER 0x00ea9690
#define FUJI_FCLOSE_HANDLER 0x00ea96e0

#define MEM_PTP_TEXT 0x00d6bfd0

#ifdef STUBS
	#include "stub.h"

	NSTUB(fuji_drive, 0x006f3f08)
	NSTUB(fuji_fopen, 0x006f0e48)
	NSTUB(fuji_fread, 0x006f0efc)
	NSTUB(fuji_fclose, 0x006f0fbc)
	NSTUB(fuji_fwrite, 0x006f0f5c)
	NSTUB(fuji_get_error, 0x006f8ba8)

	NSTUB(fuji_file_wait, 0x00ea95e4)
	NSTUB(fuji_file_reset, 0x00ea966c)

	NSTUB(fuji_io_lock, 0x00649eb4)

	NSTUB(fuji_screen_write, 0x010f0904)
	NSTUB(fuji_discard_text_buffer, 0x00d3570c)

	NSTUB(fuji_rst_write, 0x01110340)
	NSTUB(fuji_rst_config1, 0x010f2b8c)
	NSTUB(fuji_rst_config2, 0x01118198)
#endif
