// TODO: Make fujifilm/task.h, screen.h, ptp.h... (???)
#ifndef FUJI_H
#define FUJI_H

// Make text editor linter happy
#ifndef MODEL_NAME
	#include "../model/xf1_101.h"
#endif

#include <stdint.h>

// Returns current drive (DOS style)
// Crashes without SD card (???)
char fuji_drive();

// Screen text
#define TEXT_BLACK 7
#define TEXT_WHITE 1

// Write ASCII text rows to screen (permanent)
// Found by looking for "EEPRom Setting Mode"
void fuji_screen_write(char string[], int x, int y, int foreground_color, int background_color);

// Delete text buffer, does not take effect until screen updates
void fuji_discard_text_buffer();

// Found by looking for WT logging function
void *fuji_fopen(uint32_t handler, const char string[], int flag);
void *fuji_fwrite(uint32_t handler, void *fp, int n, const void *data);
void *fuji_fread(uint32_t handler, void *fp, int n, const void *data);
void *fuji_fclose(uint32_t handler, void *fp, int x, char *y);

// Weird OS/timing functions required by file API
// Crashes if these aren't used
void fuji_toggle();
void fuji_zero();

// There is no file pointer, just a single reading state
// Found by looking for functions referencing "*.*"
int fuji_dir_open(char *first, char *second, char *buffer);
int fuji_dir_next(char *buffer);

// We should be nice when there isn't much defined in model header file

// TODO: Custom handlers
#ifndef FUJI_FOPEN_HANDLER
	#define FUJI_FOPEN_HANDLER 0
#endif
#ifndef FUJI_FREAD_HANDLER
	#define FUJI_FREAD_HANDLER 0
#endif
#ifndef FUJI_FWRITE_HANDLER
	#define FUJI_FWRITE_HANDLER 0
#endif
#ifndef FUJI_FCLOSE_HANDLER
	#define FUJI_FCLOSE_HANDLER 0
#endif

#ifdef MEM_EEP_START
	#define GET_EEP(x) ((uint8_t*)MEM_EEP_START)[x]
	#define SET_EEP(x, v) ((uint8_t*)MEM_EEP_START)[x] = (uint8_t)v;
#else
	#define GET_EEP(x) /* */
	#define SET_EEP(x) /* */
#endif

// Found in EEPRom setting menu code
void fuji_apply_eeprom();

// Task creation data struct
struct FujiTask {
	uint32_t a;
	char *b;
	uint32_t c;
	uint32_t d;
	void *e;
	uint32_t f;
};

// Found in script WAIT and WAIT_SET code
int fuji_task_sleep(int ms);

// Called to init tasks on startup
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

// Highest level void function that initializes SQLite
// (Look for unusual SQLite code formatting)
void fuji_init_sqlite();

// Creates a task that is started "ms" miliseconds after this function is called.
// ms waited will be stored in buf. non zero result for error
// These were found in firmware by looking at "SoftTimerStart"/"SoftTimerStop"
int fuji_wait_task_start(int ms, int option1, void (*callback)(), int *buf);
int fuji_wait_task_stop(int bufResult);

int fuji_load_flash(int sector, int length, void *buffer, void (*callback)(int size), int flag);

#endif
