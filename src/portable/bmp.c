// Copyright (C) 2022-2023 Frontier by Daniel C - Apache License
#include <stdint.h>
#include <bmp.h>

#include <font.h>

struct FontConfig {
	int size;
}font_conf = {
	2,
};

void bmp_fill_rect(int x1, int y1, int x2, int y2, uint32_t rgb) {
	x2 += x1;
	y2 += y1;
	for (int x = x1; x < x2; x++) {
		for (int y = y1; y < y2; y++) {
			bmp_pixel(x, y, rgb);
		}
	}
}

int bmp_char(int x, int y, char c, int color) {
	// Loop to "null terminator character"
	int match = 0;
	for (int l = 0; font[l].letter != 0; l++) {
		if (font[l].letter == c) {
			match = l;
			break;
		}
	}

	if (c == 'p' || c == 'g' || c == 'j') {
		y += font_conf.size;
	}

	// Loop through 7 high 5 wide monochrome font
	int maxLength = 0;
	for (int py = 0; py < 7; py++) {
		for (int px = 0; px < 5; px++) {
			if (font[match].code[py][px] == '#') {
				if (font_conf.size == 1) {
					bmp_pixel(x + px, y + py, color);
				} else {
					bmp_fill_rect((x + px) * font_conf.size, (y + py) * font_conf.size,
						font_conf.size, font_conf.size, color);
				}

				// Dynamix width character spacing
				if (px > maxLength) {
					maxLength = px;
				}
			}
		}
	}

	return maxLength;
}

int bmp_string(int x, int y, char *string, int color) {
	int cx = x;
	int cy = y;

	// for x2 size
	cy /= font_conf.size;
	cx /= font_conf.size;

	for (int c = 0; string[c] != '\0'; c++) {
		if (string[c] == '\n') {
			cx = x / font_conf.size;
			cy += 7 + font_conf.size;
			continue;
		}

		if (string[c] == ' ') {
			cx += 5;
		} else {
			cx += bmp_char(cx, cy, string[c], color) + 3;
		}
	}

	return cx;
}

typedef int bmp_shader(int r, int g, int b);

int bmp_render_bmp_shader(void* data, int x, int y, bmp_shader *shader) {
	// BMP metadata is variable, has no definitive header
	uint32_t width = *(uint32_t*)((uint8_t*)data + 18);
	uint32_t height = *(uint32_t*)((uint8_t*)data + 22);

	uint32_t bytes_per_pixel = *(uint16_t*)((uint8_t*)data + 28) / 8;
	uint32_t padding_bytes_per_row = (4 - (width * bytes_per_pixel) % 4) % 4;

	uint32_t row_start = height - 1;
	for (int i = 0; i < height; i++) {
		uint8_t* row_data = (uint8_t*)data + *(uint32_t*)((uint8_t*)data + 10)
			+ (row_start * (width * bytes_per_pixel + padding_bytes_per_row));

		for (int j = 0; j < width; j++) {
			uint32_t pixel_offset = j * bytes_per_pixel;

			uint8_t blue = *(row_data + pixel_offset);
			uint8_t green = *(row_data + pixel_offset + 1);
			uint8_t red = *(row_data + pixel_offset + 2);

			uint32_t color;
			if (shader == 0) {
				color = (red << 16) | (green << 8) | blue;
			} else {
				color = shader(red, green, blue);
			}

			bmp_pixel(x + j, y + i, color);
		}

		row_start--;
	}

	return width;
}

int bmp_render_bmp(void* data, int x, int y) {
	return bmp_render_bmp_shader(data, x, y, 0);
}

int bmp_blue_shade(int r, int g, int b) {
	if (r == 0 && g == 0 && b == 0) {
		return (r << 16) | (g << 8) | (b + 100);
	} else {
		return (r << 16) | (g << 8) | b;
	}
}

int bmp_render_bmp_selected(void* data, int x, int y) {
	return bmp_render_bmp_shader(data, x, y, bmp_blue_shade);
}
