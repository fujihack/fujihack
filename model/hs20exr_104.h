/*
This is an information file for the Fujifilm HS20EXR.
*/

// Custom firmware seems to work (Just reverse a word in FPUPDATE.DAT)
#define CAN_CUSTOM_FIRMWARE

// Can inject and execute code in the printim function
#define PRINTIM_HACK_WORKS

#define MODEL_NAME "Fujifilm HS20EXR"
#define MODEL_CODE "62306231623262336234623562366237623862397382"

#define MEM_STRNCPY 0x001e1af8
#define MEM_SUBTRING 0x001e1af8
#define MEM_STRNCMP 0x001e1e38

// Prints some text into an image when
// it is taken. Around 400 bytes long.
#define FIRMWARE_PRINTIM 0x0040674c

#define MEM_START 0x00db6568 - 10000
#define TEXT_START 0x0074e5b0 - 10000

#define MEM_EEP_START 0x4138a1c0

// Empty area is larger than offset, so
// we will just put in the offset instead
#define COPY_LENGTH MEM_START - TEXT_START
