/*
This is an information file for the Fujifilm HS20EXR.
*/

// Where payload starts relative to the firmware,
// and where all of the addresses here start
#define PAYLOAD_START 4 + 512 + 16

// Prints some text into an image when
// it is taken
#define MEM_INJECTION 0x0040674c

#define MEM_MEMCPY 0x003fd080