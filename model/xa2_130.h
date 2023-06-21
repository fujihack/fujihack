/*
Fujifilm X-A2
Mirrorless
Released March 2015
https://en.wikipedia.org/wiki/Fujifilm_X-A2
*/

#define MODEL_NAME "Fujifilm X-A2"
#define MODEL_CODE "00050701000507020005070400050709"
#define FIRM_URL "https://dl.fujifilm-x.com/support/firmware/x-a2-130-oqijkawt/FWUP0006.DAT"
#define S3_FILE "C:\\IMFIDX10\\LX30B.S3"
#define CODE_ARM

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 480

// Dead code on this model, can be used as dummy space
#define FIRM_IMG_PROPS 0x00598aec
#define FIRM_IMG_PROPS_MAX 2000

#define FIRM_RST_WRITE 0x005b0388
#define FIRM_RST_CONFIG1 0x00592bd4
#define FIRM_RST_CONFIG2 0x005b81e0

#define FIRM_INSTAX_MENU 0x0059f604
#define FIRM_INSTAX_MENU_MAX 400
#define MEM_INSTAX_MENU 0x010ff5bc

// Prints "USB"
#define FIRM_USB_SCREEN 0x005ae41c

#define MEM_PTP_TEXT 0x00d6bfd0
#define MEM_PTP_9805 0x00D60870
#define MEM_PTP_RETURN 0x00D5EAAC

#define MEM_OPENGL_BUFFERS 0x007fd324

#define MEM_INPUT_MAP 0x00931c80

// Quest to find an area that the camera doesn't care about
#define MEM_UNUSED_SPACE 0x0142a640

#define MEM_EEP_START 0x41acd800

#define MEM_RUN_DEV_MODE 0x00d35774

// Managed by "timer" task
#define MEM_MS_TIMER 0x00917ce0

#define MEM_TEXT_LAYERS 0x16facb4

#define MEM_GET_REC_LIMIT 0x010e5d2c

#define MEM_SEARCHTBL_CALL_HIJACK 0x012598a4
#define MEM_SEARCHTBL_TASK 0x01259874

#ifdef STUBS
	#include "stub.h"

	NSTUB(fuji_drive, 0x006f3f08)
	NSTUB(fuji_fopen, 0x006f0e48)
	NSTUB(fuji_fread, 0x006f0efc)
	NSTUB(fuji_fclose, 0x006f0fbc)
	NSTUB(fuji_fwrite, 0x006f0f5c)
	NSTUB(fuji_get_error, 0x006f8ba8)
	NSTUB(fuji_fseek, 0x006f10d8)

	NSTUB(fuji_file_wait, 0x00ea95e4)
	NSTUB(fuji_file_reset, 0x00ea966c)
	NSTUB(fuji_fstats, 0x006f1684)

	NSTUB(fuji_wait_task_start, 0x00670134)
	NSTUB(fuji_wait_task_stop, 0x0067032c)
	NSTUB(fuji_task_sleep, 0x006f84e8)
	NSTUB(fuji_task_event, 0x006f983c)

	NSTUB(fuji_io_lock, 0x00649eb4)

	NSTUB(fuji_screen_write, 0x010f0904)
	NSTUB(fuji_discard_text_buffer, 0x010f0a70)

	NSTUB(fuji_rst_write, 0x01110340)
	NSTUB(fuji_rst_config1, 0x010f2b8c)
	NSTUB(fuji_rst_config2, 0x01118198)

	NSTUB(sqlite_snprintf, 0x013ee680)
	NSTUB(fuji_init_sqlite, 0x01258e80)
	NSTUB(sqlite_exec, 0x0141611c)
	NSTUB(sqlite_mallocAlarm, 0x013ed0f0)

	NSTUB(fuji_press_key, 0x00ea93f8)
	NSTUB(fuji_press_key_alias, 0x00ea98c4)

	NSTUB(fuji_get_task_id, 0x006f84b8)
#endif

#define MEM_RTOS_FUNCTIONS 0x0004dae0

// sqlite3_mem_methods
#define SQLITE_MEM_METHODS 0x01427bf8
