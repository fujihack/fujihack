#include <fujifilm.h>

int last_file_err = 0;
int last_file_id = 0;
int last_bytes_written = 0;

void fopen_handler(int error, int id, int x, int y) {
	fuji_file_reset();
	last_file_err = error;
	last_file_id = id;
}
