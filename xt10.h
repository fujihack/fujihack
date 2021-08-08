/*
Fujifilm X-T10

*/

#define MODEL_NAME "Fujifilm X-T10"

// This only works for SQLite code. Other code relies
// on strings somewhere else. HS20EXR firmware can be
// looked at in order to correctly align other strings.

// Where the code that references "out of memory" is
#define OUT_OF_MEMORY_CODE 0x00bd8954

// Location where code thinks "out of memory" is
#define OUT_OF_MEMORY_REF 0x1f54c3c

// Where "out of memory" actually resides, in the
// file that dump.c generates
#define OUT_OF_MEMORY_REAL 0x00bf4c84

#define MEM_START OUT_OF_MEMORY_REF - 10000
#define TEXT_START OUT_OF_MEMORY_REAL - 10000
#define COPY_LENGTH 10000 + 6052

/*

Where fw thinks "OSD DEBUG MODE SCREEN SELECT" is: 0x01b59bd4
Where it actually is:                              0x007f9c1c

*/

#define MEM_START2 0x01b59bd4 - 4960
#define TEXT_START2 0x007f9c1c - 4960
#define COPY_LENGTH2 79024 + 4960