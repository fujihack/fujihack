#ifndef FUJI_TASK_H
#define FUJI_TASK_H

#pragma pack(push, 1)

#include <stdint.h>

struct FujiEventRequest {
	uint16_t flag;
	uint8_t curr_tsk_id;
	uint8_t dest_tsk_id;
	uint32_t a; // 0
	uint32_t b; // 0
};

struct FujiTaskBuffer {
	char blah[48];
};

#pragma pack(pop)

int fuji_task_event(int tsk_id, struct FujiEventRequest *req);

// Creates a task that is started "ms" miliseconds after this function is called.
// ms waited will be stored in buf. non zero result for error
// These were found in firmware by looking at "SoftTimerStart"/"SoftTimerStop"
int fuji_wait_task_start(int ms, int option1, void (*callback)(), int *buf);
int fuji_wait_task_stop(int bufResult);

#endif
