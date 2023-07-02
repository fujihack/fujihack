// POSIX Compliant layer over Fuji RTOS API

#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>

#include "ff_io.h"

int last_file_error = 0;
int last_file_x = 0;

// Holds the current file position at index fd
int opens[100] = {0};

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

	int flag = 0;
	if ((rflag | S_IRUSR) & S_IRUSR) {
		flag = 0;
	} else if ((rflag | S_IWUSR) & S_IWUSR) {
		flag = 1;
	}

	fuji_file_wait();
	int fd = fuji_fopen(file_handler, pathname, flag);
	fuji_file_wait();
	fuji_file_reset();

	opens[fd % sizeof(opens)] = 0;

	if (last_file_error == 0) {
		return fd;
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

	opens[fd % sizeof(opens)] += bytes;

	if (last_file_error == 0) {
		return last_file_x;
	} else {
		return -1;
	}
}

#if 1
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	int fd = fileno(stream);

	fuji_file_wait();
	fuji_fread(file_handler, fd, size * nmemb, ptr);
	fuji_file_wait();
	fuji_file_reset();

	//printf("fread %d=%d", size * nmemb, last_file_x);

	opens[fd % sizeof(opens)] += last_file_x;

	if (last_file_error == 0) {
		return last_file_x;
	} else {
		return 0;
	}
}
#endif

int _read(int fd, void *buf, int bytes) {
	while (1);
	fuji_file_wait();
	fuji_fread(file_handler, fd, bytes, buf);
	fuji_file_wait();
	fuji_file_reset();

	opens[fd % sizeof(opens)] += bytes;

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
		opens[fd % sizeof(opens)] = offset;
	} else if (whence == SEEK_CUR) {
		whence = FUJI_FILE_CURR;
		opens[fd % sizeof(opens)] += offset;
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

	return opens[fd % sizeof(opens)];
}

int _stat(const char *path, struct stat *buf) {
	fuji_file_wait();
	int fd = fuji_fopen(file_handler, path, 0);
	fuji_file_wait();
	fuji_file_reset();

	if (last_file_error != 0) return -1;

	struct FujiStats stats;
	fuji_fstats(fd, &stats, fd);	
	buf->st_size = (int)stats.size;

	fuji_file_wait();
	fuji_fclose(file_handler, fd, 0, 0);
	fuji_file_wait();
	fuji_file_reset();

	return 0;
}
