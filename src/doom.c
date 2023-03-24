#include <io.h>
#include <rst.h>

#include <doomkeys.h>
#include <m_argv.h>
#include <doomgeneric.h>

void DG_Init() {
	printf("Init bmp\n");
	//sys_init_bmp();
}

void DG_DrawFrame() {

}

void DG_SleepMs(uint32_t ms) {
	fuji_task_sleep(ms);
}

uint32_t DG_GetTicksMs() {
	return sys_get_ticks();
}

void DG_SetWindowTitle(const char * title) {
	puts("Window title");
}

int DG_GetKey(int* pressed, unsigned char* key) {
}
