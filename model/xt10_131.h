/*
Fujifilm X-T10

*/

#define MODEL_NAME "Fujifilm X-T10"
#define MODEL_CODE "0005100100051002000510040005100500051007000510090005101"

// Code triggered when a picture is taken
//#define FIRM_TAKEPIC 0x0096cc80

// PTP/USB Code
//#define FIRM_PTP 0x01e7c718

/*

X-T10 has 3 sets of strings that are loaded seperately
during the firmware update. To identify them, I referred
to HS20EXR code, which has all strings loaded in one place.

First string copy, for SQLite code.

*/

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

Second string copy needed.

Where fw thinks "OSD DEBUG MODE SCREEN SELECT" is: 0x01b59bd4
Where it actually is:                              0x007f9c1c

*/

#define MEM_START2 0x01b59bd4 - 4960
#define TEXT_START2 0x007f9c1c - 4960
#define COPY_LENGTH2 79024 + 4960

/*

Yet another string copy needed...

Where fw thinks "PrintIM" is: 0x01cd6de8
Where "PrintIM" actually is:  0x00976e30

*/

#define MEM_START3 0x01cd6de8 - 431
#define TEXT_START3 0x00976e30 - 431
#define COPY_LENGTH3 0x281a30
