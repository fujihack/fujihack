#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

extern uint32_t screen_buffer;

void disp_pixel(int x, int y, int col);
void disp_clear(int col);
void disp_rect(int x1, int y1, int w1, int h1, int col);

#endif
