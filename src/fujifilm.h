// TODO: Make fujifilm/task.h, screen.h, ptp.h... (???)
#ifndef FUJI_H
#define FUJI_H

#include <stdint.h>

// Returns current drive (DOS style)
// Crashes without SD card (???)
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

#define GET_EEP(x) ((uint8_t*)MEM_EEP_START)[x]
#define SET_EEP(x, v) ((uint8_t*)MEM_EEP_START)[x] = (uint8_t)v;

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

void fuji_init_sqlite();

// Creates a task that is started "ms" miliseconds after this function is called.
// ms waited will be stored in buf. non zero result for error
// These were found in firmware by looking at "SoftTimerStart"/"SoftTimerStop"
int fuji_wait_task_start(int ms, int option1, void (*callback)(), int *buf);
int fuji_wait_task_stop(int bufResult);

#endif
