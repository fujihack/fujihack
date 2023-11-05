#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

#include <sys.h>

void syscall(int v);

int sys_mem_in_use = 0;

void sys_key_status() {
	
}

int sys_check_key(int key) {

}

void msleep(int ms) {

}

void exit(int status) {
}

void abort() {
}

void sys_dump() {
}

int sys_segment(void *start, uint32_t length) {
}

int sys_get_ticks() {
}
int sys_getchar() {
	
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
