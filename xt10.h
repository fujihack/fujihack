/*
Fujifilm X-T10

*/

#define MODEL_NAME "Fujifilm X-T10"

// Location where code thinks "out of memory" is
#define OUT_OF_MEMORY_REF 0x00605f8c

// Where "out of memory" actually resides, in the
// file that dump.c generates
#define OUT_OF_MEMORY_REAL 0x00bf4c84


#define MEM_START 0x00605f8c - 10000
#define TEXT_START 0x00bf4c84 - 10000
#define COPY_LENGTH MEM_START - TEXT_START