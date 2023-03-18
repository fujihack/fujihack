#include "io.h"
#include "rst.h"
#include "sqlite.h"
#include "screen.h"

__asm__(
	".global sprintf\n"
	"sprintf:\n"
	//"mov r7, r6\n"
	//"mov r6, r5\n"
	//"mov r5, r4\n"
	//"mov r4, r3\n"
	"mov r3, r2\n"
	"mov r2, r1\n"
	"mov r1, r0\n"
	"mov r0, #0xffff\n"
	"b sqlite_snprintf\n"
);

// int errno_ = 0;
// 
// void *__errno() {
	// return &errno_;
// }

int col_y = 1;
void uart_str(char *string) {
	if (col_y == 10) {
		fuji_discard_text_buffer();
		fuji_discard_text_buffer();
		col_y = 0;
	}

	fuji_screen_write(string, 1, col_y, 0, 7);
	col_y++;
}
