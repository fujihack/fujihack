#ifndef FUJI_SQLITE_H
#define FUJI_SQLITE_H

void sqlite_snprintf(int size, char *buf, char *fmt, ...);

// Why not :)
#define sprintf(buf, fmt, ...) \
	sqlite_snprintf(-1, buf, fmt, __VA_ARGS__)

#define snprintf(buf, size, fmt, ...) \
	sqlite_snprintf(size, buf, fmt, __VA_ARGS__)

#endif
