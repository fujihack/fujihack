#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <sys/stat.h>

#include "emu.h"

void syscall(int v);

int _fstat(int fd, void *stat) {
	return 0;
}

int _stat(const char *path, struct stat *buf) {
	((uintptr_t *)SYS_REGS)[0] = (uintptr_t)path;
	syscall(SYS_FILE_SIZE);
	buf->st_size = ((int *)SYS_READ_REGS)[0];
	return 0;
}

int _open(char *pathname, int oflag, int rflag) {
	((uintptr_t *)SYS_REGS)[0] = (uintptr_t)pathname;
	((int *)SYS_REGS)[1] = oflag;
	((int *)SYS_REGS)[2] = rflag;
	syscall(SYS_FOPEN);
	return ((int *)SYS_READ_REGS)[0];
}

int _write(int fd, void *buf, int bytes) {
	((int *)SYS_REGS)[0] = fd;
	((uintptr_t *)SYS_REGS)[1] = (uintptr_t)buf;
	((int *)SYS_REGS)[2] = bytes;
	syscall(SYS_FWRITE);
	return ((int *)SYS_READ_REGS)[0];
}

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	((int *)SYS_REGS)[0] = fileno(stream);
	((uintptr_t *)SYS_REGS)[1] = (uintptr_t)ptr;
	((int *)SYS_REGS)[2] = (nmemb * size);
	syscall(SYS_FREAD);
	return ((int *)SYS_READ_REGS)[0];	
}

int _read(int fd, void *buf, int bytes) {
	return -1;
}

int _close(int fd) {
	((int *)SYS_REGS)[0] = fd;
	syscall(SYS_FCLOSE);
	return ((int *)SYS_READ_REGS)[0];
}

int _lseek(int fd, int offset, uint32_t whence) {
	((int *)SYS_REGS)[0] = fd;
	((int *)SYS_REGS)[1] = offset;
	((uint32_t *)SYS_REGS)[2] = whence;
	syscall(SYS_FSEEK);
	return ((int *)SYS_READ_REGS)[0];
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
