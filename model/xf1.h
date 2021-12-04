/*
Fujifilm X-T10

*/

#define MODEL_NAME "Fujifilm XF-1"

// Confirmed tests:

// Executer has been tested, and is confirmed to be working
#define CAN_DO_EXECUTER

// Custom firmware seems to work (Just reverse a word in FPUPDATE.DAT)
#define CAN_CUSTOM_FIRMWARE

// Can inject and execute code in the printim function
#define PRINTIM_HACK_WORKS

/*
These are stubs for the "lay" target,
which rearrages the firmware file
as if it were in memory.

In most cases, the firmware thinks the
strings should be somewhere else in
the firmware file, although this
could also be somewhere outside the
firmware file.

In order to find these addresses, code
must be matched up with an external
source. For the first time this was
done, firmware code was matched up
alongside the SQLite source code, which
is included on newer models.
*/

// Where code thinks the data should be:
#define MEM_START 0x011ea108 - 0x10000

// Where the data actually is:
#define TEXT_START 0x00492150 - 0x10000

// How much data should be copied
#define COPY_LENGTH 0x500000

// Code that writes "PrintIM" to JPEG images. A safe place
// To execute code.
#define FIRMWARE_PRINTIM 0x00516c90

/*
Stubs are marked here:
*/

// Memory address where code can be copied. Need
// A bunch of useless bytes that don't seem important
#define MEM_FREE_SPACE 0x00e572e8

// Where to hack on the PTP thumbnail function, 
// Seems to have bytes [0xf0, 0x4d, 0x2d, 0xe9]
#define MEM_PTP_THUMBNAIL 0x00e56fbc





// etc porting notes
#define PTP_INFO 0x00e5dabc
#define MEM_MODEL_TEXT 0x00e5e228

/*

0x0974b978
found '\AUTO_ACT.SCR'

0x0083b684
found 'p: 1.0; '

0x83b684
found 'ot.b' (ffboot.bin)

*/
