#ifndef FF_TASK_H
#define FF_TASK_H

#pragma pack(push, 1)

#include <stdint.h>

struct FujiEventReq {
	uint16_t event_code;
	uint8_t current_tsk_id;
	uint8_t target_tsk_id;
	uint32_t target_tsk_id2;
	uint32_t *unknown;
};

int fuji_task_event(int id, struct FujiEventReq *req);

// Task creation data struct
struct FujiTask {
	uint32_t a;
	char *b;
	uint32_t c;
	uint32_t d;
	void *e;
	uint32_t f;
};

int fuji_get_task_id();

// (Found in script WAIT and WAIT_SET code)
int fuji_task_sleep(int ms);

// Called to init tasks on startup
int fuji_create_task(int x, int y, struct FujiTask *task);

struct FujiTaskBuffer {
	int a;
	int b;
	int c;
	int d;
	int e;
};

enum FujiTaskMode {
	FUJI_TASK_TIMEOUT = 0,
	FUJI_TASK_REPEAT = 1,
};

// Creates a task that is started "ms" miliseconds after this function is called.
// Returns a task ID, which is used in fuji_wait_task_stop
// ms: task is called after x ms or called every x ms
// option1: 0 for timeout delayed call, 1 is for repeating called
// These were found in firmware by looking at "SoftTimerStart"/"SoftTimerStop"
int fuji_wait_task_start(int ms, int task_mode, void (*callback)(), struct FujiTaskBuffer *buf);
int fuji_wait_task_stop(int bufResult);

// Used by OS to decompress firmware from flash (syslog DECE)
int fuji_load_flash(int sector, int length, void *buffer, void (*callback)(int size), int flag);

#pragma pack(pop)

#endif
