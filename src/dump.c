#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <fujihack.h>
#include <ff_io.h>
#include <ff_screen.h>

static void handler(int error, int x, int y, int z) {
	fuji_file_reset();
}

void fh_dump_ram() {
	fuji_screen_write("Will lock up", 1, 1, 0, 7);

	fuji_file_wait();
	int fd = fuji_fopen(handler, "C:\\RAM.BIN", 1);
	fuji_file_wait();
	fuji_file_reset();

	fuji_file_wait();
	fuji_fwrite(handler, fd, 0x10000000, 0x0);
	fuji_file_wait();
	fuji_file_reset();

	fuji_file_wait();
	fuji_fclose(handler, fd, 0, 0);
	fuji_file_wait();
	fuji_file_reset();

	fuji_screen_write("Done", 1, 2, 0, 7);
}
