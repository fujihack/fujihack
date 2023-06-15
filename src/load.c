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

int fh_load() {
	// Temporary disable the menu while writing
	//((uint32_t *)MEM_RUN_DEV_MODE)[0] = 0xe12fff1e;


	//char export[] = {0x0, 0x0, 0xa0, 0xe3, 0x1e, 0xff, 0x2f, 0xe1, };
	//memcpy((uint32_t *)MEM_RUN_DEV_MODE, export, sizeof(export));

	fuji_file_wait();
	int fp = fuji_fopen(file_handler, "C:\\DCAA\\AUTO_ACT.SCR", 0);
	fuji_file_wait();
	fuji_file_reset();
	if (last_file_error != FUJI_OK) {
		return 1;
	}

	struct FujiStats s;
	fuji_fstats(fp, &s, fp);

	fuji_file_wait();
	fuji_fread(file_handler, fp, s.size, (void *)MEM_UNUSED_SPACE);
	fuji_file_wait();
	fuji_file_reset();

	fuji_file_wait();
	fuji_fclose(file_handler, fp, 0, 0);
	fuji_file_wait();
	fuji_file_reset();

	typedef void func(void);
	func* f = (func*)MEM_UNUSED_SPACE;
	f();
	return 0;
}
