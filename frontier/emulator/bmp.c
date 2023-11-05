#define CNFG_IMPLEMENTATION
#include <rawdraw_sf.h>

#include <emulator.h>
#include <emu.h>

uint32_t *screen;

void bmp_handle_input() {
	CNFGHandleInput();
}

int bmp_render() {
	CNFGUpdateScreenWithBitmap(screen, SCREEN_WIDTH, SCREEN_HEIGHT);
	//CNFGSwapBuffers();
	return 0;
}

int bmp_setup() {
	screen = malloc(SCREEN_WIDTH * SCREEN_HEIGHT * 4);
	CNFGSetup("Rigged Emulator", SCREEN_WIDTH, SCREEN_HEIGHT);
	return 0;
}

void HandleKey(int keycode, int bDown) {
	switch (keycode) {
		case CNFG_KEY_ESCAPE: keycode = 27; break;
		case CNFG_KEY_ENTER: keycode = 13; break;
		case CNFG_KEY_BOTTOM_ARROW: keycode = 40; break;
		case CNFG_KEY_TOP_ARROW: keycode = 38; break;
		case CNFG_KEY_RIGHT_ARROW: keycode = 39; break;
		case CNFG_KEY_LEFT_ARROW: keycode = 37; break;
	}

	if (bDown == 1) {
		keys.last_key = keycode;
	} else {
		keys.last_key = 0;
	}
}

void HandleButton( int x, int y, int button, int bDown ) {
	keys.mouse_down = bDown;
}

void HandleMotion( int x, int y, int mask ) {
	keys.mouse_x = x / 2;
	keys.mouse_y = y / 2;
}

void HandleDestroy() {
	puts("Destroy");
}

