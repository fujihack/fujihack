#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <sys.h>
#include <bmp.h>
#include <buttons.h>

typedef struct {
    double x;
    double y;
} Complex;

Complex add(Complex a, Complex b) {
    Complex c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}

Complex multiply(Complex a, Complex b) {
    Complex c;
    c.x = a.x * b.x - a.y * b.y;
    c.y = a.x * b.y + a.y * b.x;
    return c;
}

double magnitude(Complex c) {
    return sqrt(c.x * c.x + c.y * c.y);
}

int mandelbrot(Complex c, int max_iter) {
    Complex z = {0, 0};
    for (int i = 0; i < max_iter; i++) {
        if (magnitude(z) > 2.0) {
            return i;
        }
        z = add(multiply(z, z), c);
    }
    return -1;
}

#define WIDTH 720
#define HEIGHT 480
#define MAX_ITER 25

int main() {
	sys_init_bmp();

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            Complex c = {(double)x / WIDTH * 4.0 - 2.0, (double)y / HEIGHT * 4.0 - 2.0};
            int iter = mandelbrot(c, MAX_ITER);
            if (iter < 0) {
            	bmp_pixel(x, y, 0);
            } else {
            	uint32_t col = 0;
            	col |= (uint32_t)(iter * 10 % 256) << 16;
            	col |= (uint32_t)(iter * 20 % 256) << 8;
            	col |= (uint32_t)(iter * 30 % 256);
            	bmp_pixel(x, y, col);
            }
        }
        bmp_apply();
    }

	puts("Printed");

	while (1) {}

    return 0;
}
