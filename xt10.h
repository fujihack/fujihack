/*
Fujifilm X-T10

*/

#define MODEL_NAME "Fujifilm X-T10"

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