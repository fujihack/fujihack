//Make it so we don't need to include any other C files in our build.
#define CNFG_IMPLEMENTATION

#include "../../rawdraw/rawdraw_sf.h"

// "Seems to work" screen buffer
#define SCREEN_WIDTH 720/2
#define SCREEN_HEIGHT 480/2

FILE *fp;
uint32_t data[SCREEN_WIDTH * SCREEN_HEIGHT];
int asd = 0;

void HandleKey( int keycode, int bDown ) {
#if 0
	if (bDown) return;
	fseek(fp, 0x20000000+((640 * 320 * 4) * asd), SEEK_SET);
	printf("%08X\n", 0x20000000+((640 * 320 * 4) * asd));
	fread(data, 1, sizeof(data), fp);
	asd++;
#endif
}

void HandleButton( int x, int y, int button, int bDown ) { }
void HandleMotion( int x, int y, int mask ) { }
void HandleDestroy() {}

int main()
{
	CNFGSetup("Fuji Emulator screen", SCREEN_WIDTH, SCREEN_HEIGHT);

	fp = fopen("/home/daniel/Desktop/dump/lv/RAM2.BIN", "rb");
	if (fp == NULL) return 0;

	fseek(fp, 0x2341c000, SEEK_SET);
	fread(data, 1, sizeof(data), fp);
	fclose(fp);

	while(CNFGHandleInput())
	{
		CNFGClearFrame();

		CNFGColor( 0xffffffff ); 

		CNFGBlitImage(data, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		CNFGSwapBuffers();
	}

	fclose(fp);
}
