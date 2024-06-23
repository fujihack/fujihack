#ifndef BMP_H
#define BMP_H

void bmp_clear(uint32_t rgb);
void bmp_apply();
void bmp_fill_rect(int x1, int y1, int x2, int y2, uint32_t rgb);
void bmp_pixel(int x, int y, uint32_t rgb);

int bmp_screen_height();
int bmp_screen_width();

int bmp_char(int x, int y, char c, int color);
int bmp_string(int x, int y, char *string, int color);
int bmp_render_bmp(void* data, int x, int y);

#endif
