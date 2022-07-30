#ifndef FUJI_SQLITE_H
#define FUJI_SQLITE_H

struct SQLiteDB {
	
};

// https://www.sqlite.org/c3ref/mprintf.html
void sqlite_snprintf(int size, char *buf, char *fmt, ...);

#if 0
// https://www.sqlite.org/c3ref/exec.html
int sqlite_exec(
	struct SQLiteDB *db,
	char *sql,
	int (*callback)(void*, int, char**, char**),
	void *arg,
	char **errmsg
);
#endif

void *sqlite_malloc(int n);

#endif
