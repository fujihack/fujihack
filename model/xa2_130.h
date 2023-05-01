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

// Dead code, can be used as temporary space
#define FIRM_IMG_PROPS 0x00598aec
#define FIRM_IMG_PROPS_MAX 2000
#define FIRM_RST_WRITE 0x005b0388
#define FIRM_RST_CONFIG1 0x00592bd4
#define FIRM_RST_CONFIG2 0x005b81e0

// Prints "USB"
#define FIRM_USB_SCREEN 0x005ae41c

#define MEM_PTP_TEXT 0x00d6bfd0
#define MEM_PTP_9805 0x00D60870
#define MEM_PTP_RETURN 0x00D5EAAC

#define MEM_OPENGL_BUFFERS 0x007fd324

#define MEM_INPUT_MAP 0x00931c80

// sqlite3_mem_methods
#define SQLITE_MEM_METHODS 0x01427bf8

// temporary flash buffer for decoding
#define MEM_FLASH_DUMP 0x10000000

// Managed by "timer" task
#define MEM_MS_TIMER 0x00917ce0

#define MEM_TEXT_LAYERS 0x16facb4

#define MEM_DEV_MODE_FUNC 0x00d35774

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
	NSTUB(fuji_discard_text_buffer, 0x00d3570c)

	NSTUB(fuji_rst_write, 0x01110340)
	NSTUB(fuji_rst_config1, 0x010f2b8c)
	NSTUB(fuji_rst_config2, 0x01118198)

	NSTUB(sqlite_snprintf, 0x013ee680)
	NSTUB(fuji_init_sqlite, 0x01258e80)
	NSTUB(sqlite_exec, 0x0141611c)
	NSTUB(sqlite_mallocAlarm, 0x013ed0f0)

	NSTUB(fuji_press_key, 0x00ea93f8)

	NSTUB(fuji_get_task_id, 0x006f84b8)
#endif

#define MEM_RTOS_FUNCTIONS 0x0004dae0

/*
Found IO table starting at 0xfff20000 with size 4
Found IO table starting at 0xfff22000 with size 4
Found IO table starting at 0xfff30414 with size 796
Found IO table starting at 0xfff38000 with size 4
Found IO table starting at 0xfff39c04 with size 8
Found IO table starting at 0xfff3c000 with size 12
Found IO table starting at 0xfff3f000 with size 4
Found IO table starting at 0xfff44000 with size 4
Found IO table starting at 0xfff48004 with size 4
Found IO table starting at 0xfff61000 with size 4
Found IO table starting at 0xfff70000 with size 4
Found IO table starting at 0xfff78018 with size 12
Found IO table starting at 0xfff84080 with size 4
Found IO table starting at 0xfff88000 with size 4
Found IO table starting at 0xfffa0004 with size 4096
Found IO table starting at 0xfffa8004 with size 60
Found IO table starting at 0xfffb2004 with size 4
*/
