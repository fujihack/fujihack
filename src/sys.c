// Defines POSIX and Frontier interface
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <sys/stat.h>

#include <sys.h>

#include <ff_io.h>
#include <ff_task.h>

int sys_check_key(int key) {
	if (key == SYS_BUTTON_QUIT) {
		key = KEY_DISPBACK;
	} else if (key == SYS_BUTTON_DOWN) {
		key = KEY_DOWN;
	} else if (key == SYS_BUTTON_UP) {
		key = KEY_UP;
	} else if (key == SYS_BUTTON_LEFT) {
		key = KEY_LEFT;
	} else if (key == SYS_BUTTON_RIGHT) {
		key = KEY_RIGHT;
	} else if (key == SYS_BUTTON_LEFT) {
		key = KEY_LEFT;
	} else if (key == SYS_BUTTON_OK) {
		key = KEY_OK;
	}

	struct FujiInputMap *m = (struct FujiInputMap *)MEM_INPUT_MAP;
	if (m->key_code == key && m->key_status == 0x0) {
		return 1;
	} else {
		return 0;
	}
}

void msleep(int ms) {
	fuji_task_sleep(ms);
}

// TODO: move to assembly
void exit(int status) {
	while (1) {}
}

void abort() {
	
}

long int sys_get_ticks() {
	return ((long int *)MEM_MS_TIMER)[0];
}

int _gettimeofday() {
	return 0;
}

int _getpid() {
	return -1;
}

int _kill(int pid, int sig) {
	return -1;
}

int _isatty(int fd) {
	return 1;
}

int _unlink(const char *x) {
	return -1;
}

int _link(const char *x, const char *b) {
	return -1;
}

int system(char *x) {
	return -1;
}

int mkdir(const char *_path, mode_t __mode) {
	return -1;
}
