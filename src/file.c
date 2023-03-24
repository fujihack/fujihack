// POSIX Compliant layer over Fuji RTOS API

#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>

#include "io.h"

int last_file_error = 0;
int last_file_x = 0;

static int opens[10];

void file_handler(int error, int x, int y, int z) {
	fuji_file_reset();
	last_file_error = error;
	last_file_x = x;
}

int _open(char *pathname, int oflag, int rflag) {
	if (pathname[0] != 'C') {
		errno = -1;
		return -1;
	}

	int flag;
	if (rflag == S_IREAD) {
		flag = 0;
	} else if (rflag == S_IWRITE) {
		flag = 1;
	} else {
		flag = 2;
	}

	fuji_file_wait();
	int f = fuji_fopen(file_handler, pathname, flag);
	fuji_file_wait();
	fuji_file_reset();

	opens[f] = 0;

	if (last_file_error == 0) {
		return f;
	} else {
		errno = -1;
		return -1;
	}
}

int _write(int fd, void *buf, int bytes) {
	fuji_file_wait();
	fuji_fwrite(file_handler, fd, bytes, buf);
	fuji_file_wait();
	fuji_file_reset();

	opens[fd] += bytes;

	if (last_file_error == 0) {
		return last_file_x;
	} else {
		return -1;
	}
}

int _read(int fd, void *buf, int bytes) {
	fuji_file_wait();
	fuji_fread(file_handler, fd, bytes, buf);
	fuji_file_wait();
	fuji_file_reset();

	opens[fd] += bytes;

	if (last_file_error == 0) {
		return last_file_x;
	} else {
		return -1;
	}
}

int _close(int fd) {
	fuji_file_wait();
	fuji_fclose(file_handler, fd, 0, 0);
	fuji_file_wait();
	fuji_file_reset();
	return 0;
}

int _fstat(FILE *fd, void *stat) {
	return 0;
}

int _lseek(int fd, int offset, uint32_t whence) {
	if (whence == SEEK_SET) {
		whence = FUJI_FILE_SET;
		opens[fd] = offset;
	} else if (whence == SEEK_CUR) {
		whence = FUJI_FILE_CURR;
		opens[fd] += offset;
		if (offset == 0) {
			return opens[fd];
		}
	} else if (whence == SEEK_END) {
		// This should only be used for checking file sizes
		struct FujiStats stats;
		fuji_fstats(fd, &stats, fd);
		return (int)stats.size;
	}

	fuji_file_wait();
	fuji_fseek(file_handler, fd, offset, 0, whence);
	fuji_file_wait();
	fuji_file_reset();

	return opens[fd];
}
