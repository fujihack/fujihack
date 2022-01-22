#ifndef FUJI_SQLITE_H
#define FUJI_SQLITE_H

void sqlite_snprintf(int size, char *buf, char *fmt, ...);

void sqlite_exec(int *fmt, ...);

// Why not :)
#define sprintf(buf, ...) \
	sqlite_snprintf(-1, buf, __VA_ARGS__)

#define snprintf(buf, size, fmt, ...) \
	sqlite_snprintf(size, buf, fmt, __VA_ARGS__)

#endif
