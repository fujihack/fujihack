/*
Studying Z3 firmware is useful since it's an older revision.

where /jobEndReason is on HS20EXR: 00e87bac

where /jobEndReason should be on Z3: 0x0030d4f4
where /jobEndReason really is on Z3: 0x00307524

How it's found: Search instruction:
cmp r2, #0x71000000 or `71 04 52 e3`

*/

#define MODEL_NAME "Fujifilm Z3"

#define MODEL_SIZE 128

#define MEM_START 0x0030d4f4 - 10000
#define TEXT_START 0x00307524 - 10000
#define COPY_LENGTH 10000 + 6052