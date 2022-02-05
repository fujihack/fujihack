#ifndef FUJI_SQLITE_H
#define FUJI_SQLITE_H

// https://www.sqlite.org/c3ref/mprintf.html
void sqlite_snprintf(int size, char *buf, char *fmt, ...);

// https://www.sqlite.org/c3ref/exec.html
int sqlite_exec(
	void *db,
	char *sql,
	int (*callback)(void*, int, char**, char**),
	void *arg,
	char **errmsg
);

#endif
