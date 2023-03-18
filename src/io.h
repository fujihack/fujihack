// Fujifilm IO
#ifndef FUJI_IO_H
#define FUJI_IO_H

#pragma pack(push, 1)

// Make text editor linter happy
#ifndef MODEL_NAME
	#include "../model/xf1_101.h"
#endif

#include <stdint.h>

// Returns current drive (DOS style)
// Crashes without SD card (???)
char fuji_drive();

// Note: FILE IO functions found by looking for WT logging function

struct FujiStats {
	char filename[0x30];
	uint32_t a;
	uint32_t size;
	uint32_t b;
	char created[0x48];
	char modified[0x48];
};

enum FujiFileError {
	FUJI_OK = 0,
	FUJI_TOO_MANY_HANDLES = 8,
	FUJI_EOF = 14,
	// 9
	// 14
	// 1
	// 5
	// 2
};

// fseek whence
#define FUJI_FILE_SET 0
#define FUJI_FILE_CURR 1

#define FUJI_FILE_HANDLER void (*handler)(int error, int id, int, int)

// Returns an file IO ID (increments like a stack).
int fuji_fopen(FUJI_FILE_HANDLER, const char string[], int flag);
int fuji_fwrite(FUJI_FILE_HANDLER, int fp, int n, const void *data);
int fuji_fread(FUJI_FILE_HANDLER, int fp, int n, void *data);
int fuji_fclose(FUJI_FILE_HANDLER, int fp, int x, int y);
int fuji_fseek(FUJI_FILE_HANDLER, int fp, int pos, int a, int whence);
int fuji_fstats(int fp, struct FujiStats *s, int fp2);

// Context sensitive, crashes in USB task
int fuji_get_error(int type, int *result, int flag);

// Used inbetween file operations to gain access to filesystem
void fuji_file_wait();
void fuji_file_reset();

// There is no file pointer, just a single reading state
// Found by looking for functions referencing "*.*"
int fuji_dir_open(char *first, char *second, char *buffer);
int fuji_dir_next(char *buffer);

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
// (Look for unusual SQLite code formatting), "FFDB"
void fuji_init_sqlite();

// Creates a task that is started "ms" miliseconds after this function is called.
// ms waited will be stored in buf. non zero result for error
// These were found in firmware by looking at "SoftTimerStart"/"SoftTimerStop"
int fuji_wait_task_start(int ms, int option1, void (*callback)(), int *buf);
int fuji_wait_task_stop(int bufResult);

// Used by OS to decompress firmware from flash (syslog DECE)
int fuji_load_flash(int sector, int length, void *buffer, void (*callback)(int size), int flag);

#pragma pack(pop)

#endif
