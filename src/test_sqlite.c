#include "sqlite.h"
#include "fujifilm.h"

int test_callback(void *opq, int argc, char **argv, char **colname) {
	char buffer[64];
	sqlite_snprintf(sizeof(buffer), buffer, "== %s", argv[0]);
	fuji_screen_write(buffer, 1, 3, 0, 7);
	return 0;
}

void run_sqlite_test() {
	struct SQLiteDB *db = (struct SQLiteDB*)(((uintptr_t*)MEM_SQLITE_STRUCT)[3]);

	if (db == 0) {
		fuji_init_sqlite();
	}

	char *errmsg = 0;

	int r = sqlite_exec(db, "SELECT 123 + 1;", test_callback, 0, &errmsg);

	char buffer[64];
	sqlite_snprintf(sizeof(buffer), buffer, "Return code: %x", r);
	fuji_screen_write(buffer, 1, 1, 0, 7);
	if (errmsg) {
		sqlite_snprintf(sizeof(buffer), buffer, "%s", errmsg);
		fuji_screen_write(buffer, 1, 2, 0, 7);
	} else {
		fuji_screen_write("No err msg", 1, 2, 0, 7);
	}
}
