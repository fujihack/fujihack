// Fuji rasterizer and screen related things
#ifndef RST_H
#define RST_H

#pragma pack(push, 1)

// Fuji seems indecisive on what buffer to use - below is repeated 3 times @ MEM_OPENGL_BUFFERS
// but dat1 and dat2 is different. Don't know what it means, or if it's a part of OpenGL itself.
// Controlled by vglib task.
struct OpenGLBuffers {
	uint16_t dat1;
	uint16_t dat2;
	uint32_t layer1;
	uint32_t layer2;
	uint32_t layer3;
};

// Screen text
#define TEXT_BLACK 7
#define TEXT_BLUE 1
#define TEXT_WHITE 0

// Delete text buffer, does not take effect until screen updates
void fuji_discard_text_buffer();

// Write permanent ASCII text to screen
void fuji_screen_write(char string[], int x, int y, int foreground_color, int background_color);

// These are typically used in order in source code
void fuji_rst_config1(unsigned short x); // Layer, or something, typically 0xf
void fuji_rst_config2(unsigned short x); // BG/FG color

// Most of these can be figured out by looking in RAM for
// "Script version", "Software version" strings

#include <stdint.h>

struct RstText {
	uint32_t length; // number of entries
	uint32_t active; // 1 or 0
};

struct RstTextEntry {
	uint8_t x;
	uint8_t y;
	uint8_t bg;
	uint8_t fg;
	uint8_t unicode_string[66]; // separated by 0xE1 instead of 0x0
};

// Screen text
// TODO: rename -> FUJI_
#define TEXT_BLACK 7
#define TEXT_BLUE 1
#define TEXT_WHITE 0

// Delete text buffer, does not take effect until screen updates
void fuji_discard_text_buffer();

// Write permanent ASCII text to screen
void fuji_screen_write(char string[], int x, int y, int foreground_color, int background_color);

// These are typically used in order in source code
void fuji_rst_config1(unsigned short x); // Layer, or something, typically 0xf
void fuji_rst_config2(unsigned short x); // BG/FG color

// Most of these can be figured out by looking in RAM for
// "Script version", "Software version" strings

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

#pragma pack(pop)

#endif
