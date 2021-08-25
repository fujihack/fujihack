/*
Fujifilm X-T10

*/

#define MODEL_NAME "Fujifilm XF-1"

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