// Fuji rasterizer defs
#ifndef RST_H
#define RST_H

#include <stdint.h>

#define RGB(r, g, b) (uint8_t[]){r, g, b}

#define RST_COL_RED RGB(0xff, 0, 0)
#define RST_COL_BLACK RGB(0, 0, 0)

void fuji_rst_rect(
	int param1; // screen layer?
	int param2; // layer order?

	int x1;
	int y1;
	int x2;
	int y2;

	// ????
	int param3;
	int param4;

	int thickness;
	uint8_t color[3];
	int transparency;
);

void fuji_rst_write(int x, int dy, char *string);
void fuji_rst_config1(int x); // color?
void fuji_rst_config2(int x); // layer?

#endif
