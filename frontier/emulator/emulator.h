#ifndef _EMU_H
#define _EMU_H

int emulator(char *filename);

struct Keys {
	int last_key;
	int mouse_x;
	int mouse_y;
	int mouse_down;
};

extern struct Keys keys;

#endif
