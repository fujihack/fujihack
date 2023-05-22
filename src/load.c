// Load Frontier hack.bin
#include "ff_sqlite.h"
#include "ff_io.h"

int last_file_error = 0;
int last_file_x = 0;

void file_handler(int error, int x, int y, int z) {
	fuji_file_reset();
	last_file_error = error;
	last_file_x = x;
}

void *fh_load() {
	((uint32_t *)MEM_RUN_DEV_MODE)[0] = 0xe12fff1e;

	fuji_file_wait();
	int fp = fuji_fopen(file_handler, "C:\\DCAA\\AUTO_ACT.SCR", 0);
	fuji_file_wait();
	fuji_file_reset();
	if (last_file_error != FUJI_OK) {
		return 0;
	}

	struct FujiStats s;
	fuji_fstats(fp, &s, fp);

	fuji_file_wait();
	fuji_fread(file_handler, fp, s.size, (void *)MEM_FLASH_DUMP);
	fuji_file_wait();
	fuji_file_reset();

	fuji_file_wait();
	fuji_fclose(file_handler, fp, 0, 0);
	fuji_file_wait();
	fuji_file_reset();

	return (void *)MEM_FLASH_DUMP;
}
