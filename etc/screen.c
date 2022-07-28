//Make it so we don't need to include any other C files in our build.
#define CNFG_IMPLEMENTATION

#include "../../rawdraw/rawdraw_sf.h"

void HandleKey( int keycode, int bDown ) { }
void HandleButton( int x, int y, int button, int bDown ) { }
void HandleMotion( int x, int y, int mask ) { }
void HandleDestroy() { }

// "Seems to work" screen buffer
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 320

#define MEM_SCREEN_BUFFER (0x01901800 + (640 * 4 * 170) - 520)
#define GET_SCREEN_LAYER(x) (MEM_SCREEN_BUFFER + (SCREEN_WIDTH * SCREEN_HEIGHT * 4) * x)


int main()
{
	CNFGSetup("Fuji Emulator screen", SCREEN_WIDTH, SCREEN_HEIGHT);

	uint32_t data[SCREEN_WIDTH * SCREEN_HEIGHT];

	FILE *fp = fopen("/home/daniel/Documents/dump/RAM1.BIN", "r");
	fseek(fp, GET_SCREEN_LAYER(3), SEEK_SET);
	fread(data, 1, sizeof(data), fp);
	fclose(fp);

	printf("0x%x\n", GET_SCREEN_LAYER(3));

	while(CNFGHandleInput())
	{
		CNFGClearFrame();

		CNFGColor( 0xffffffff ); 

		CNFGBlitImage(data, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		CNFGSwapBuffers();
	}
}
