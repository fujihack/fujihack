#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <sys/stat.h>

// TODO: move to assembly
void exit(int status) {

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
