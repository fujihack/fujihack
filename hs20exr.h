/*
This is an information file for the Fujifilm HS20EXR,
In case this hack will be ported.
*/

#define MODEL_NAME "Fujifilm HS20EXR"

// Where payload starts relative to the firmware,
// and where all of the addresses here start
#define PAYLOAD_START 4 + 512 + 16

// Prints some text into an image when
// it is taken. Around 400 bytes long.
#define MEM_INJECTION 0x0040674c

#define MEM_START 0x00db6568 - 10000
#define TEXT_START 0x0074e5b0 - 10000

// Empty area is larger than offset, so
// we will just put in the offset instead
#define COPY_LENGTH MEM_START - TEXT_START