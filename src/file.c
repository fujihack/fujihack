// This will provide POSIX wrappers over Fujifilm RTOS functions
// for compatibility.

#include <stdio.h>
#include <sys/stat.h>

#include "fujifilm.h"
#include "fujihack.h"

int last_file_error = 0;
int last_file_x = 0;

void file_handler(int error, int x, int y, int z) {
	fuji_file_reset();
	last_file_error = error;
	last_file_x = x;
}

int _open(char *pathname, int oflag, int rflag) {
	int flag;
	if (rflag == S_IREAD) {
		flag = 0;
	} else if (rflag == S_IWRITE) {
		flag = 1;
	} else {
		flag = 2;
	}

	fuji_toggle();
	int f = fuji_fopen(file_handler, pathname, flag);
	fuji_toggle();
	fuji_zero();

	if (last_file_error == 0) {
		return f;
	} else {
		return -1;
	}
}

int _write(int fd, void *buf, int bytes) {
	fuji_toggle();
	fuji_fwrite(file_handler, fd, bytes, buf);
	fuji_toggle();
	fuji_zero();

	if (last_file_error == 0) {
		return last_file_x;
	} else {
		return -1;
	}
}

int _read(int fd, void *buf, int bytes) {
	fuji_toggle();
	fuji_fread(file_handler, fd, bytes, buf);
	fuji_toggle();
	fuji_zero();

	if (last_file_error == 0) {
		return last_file_x;
	} else {
		return -1;
	}
}

int _close(int fd) {
	fuji_toggle();
	fuji_fclose(file_handler, fd, 0, 0);
	fuji_toggle();
	fuji_zero();
	return 0;
}

int _fstat(FILE *fd, void *stat) {
	return 0;
}

int _lseek(int fd, int offset, uint32_t whence) {
	return -1;
}
