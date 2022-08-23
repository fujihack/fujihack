// TODO: Make fujifilm/task.h, screen.h, ptp.h... (???)
#ifndef FUJI_H
#define FUJI_H

#include <stdint.h>

// Fujifilm uses 4 bytes per pixel, multiple layer display system.
// Each pixel is your typical hex code #aabbcc, with the
// last 2 bytes are transparency (????)
#define COL_BLACK 0x00000000
#define COL_WHITE 0xffffffff

// RTOS malloc, seems to be task specific
unsigned int fuji_malloc(int n, void *addr, int mode);

// Returns current drive (DOS style)
char fuji_drive();

// Screen text
#define TEXT_BLACK 7
#define TEXT_WHITE 1

// Write ASCII text rows to screen
void fuji_screen_write(char string[], int x, int y, int foreground_color, int background_color);

// Delete text buffer, does not take effect until screen updates
void fuji_discard_text_buffer();

void *fuji_fopen(uint32_t handler, const char string[], int flag);
void *fuji_fwrite(uint32_t handler, void *fp, int n, const void *data);
void *fuji_fread(uint32_t handler, void *fp, int n, const void *data);
void *fuji_fclose(uint32_t handler, void *fp, int x, char *y);

// There is no file pointer, just a single reading state
int fuji_dir_open(char *first, char *second, char *buffer);
int fuji_dir_next(char *buffer);

// Weird OS/timing functions required by file API
void fuji_toggle();
void fuji_zero();

#ifdef MEM_EEP_START
	#define GET_EEP(x) ((uint8_t*)MEM_EEP_START)[x]
	#define SET_EEP(x, v) ((uint8_t*)MEM_EEP_START)[x] = (uint8_t)v;
#endif

// Task creation data struct
struct FujiTask {
	uint32_t a;
	char *b;
	uint32_t c;
	uint32_t d;
	void *e;
	uint32_t f;
};

int fuji_task_sleep(int ms);

// Seems to just crash the camera
int fuji_create_task(int x, int y, struct FujiTask *task);

struct FujiInputMap {
	uint32_t key_code;
	uint32_t x;
	uint32_t key_status;
	int gyro;
	int accel;
	uint32_t a;
	uint32_t b;
	uint32_t c;
};

struct FujiPTPParams {
	uint32_t code; // ptp command code
	uint32_t transid; // ?
	uint32_t x; // ?
	uint32_t length; // ?
	uint32_t param1;
	uint32_t param2;
};

struct FujiPTPData {
	uint32_t a;
	// ?????
};

// Function for each PTP command
void fuji_ptp_function(uint8_t mode, struct FujiPTPParams *params, struct FujiPTPData *data);

// "x" is generally 0
void fuji_ptp_finish(struct FujiPTPParams *params, int retcode, int retcode2);
void fuji_ptp_return(int retcode, int x);

void fuji_init_sqlite();

#endif
