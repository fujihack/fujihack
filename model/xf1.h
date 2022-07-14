/*
Fujifilm X-F1 Information File
*/

#define MODEL_NAME "Fujifilm XF-1"
#define MODEL_CODE "000192710001927200019273000192740001927500019276000192770001927800019279000192810001928200019286"

// Confirmed tests:
#define CAN_DO_EXECUTER
#define CAN_CUSTOM_FIRMWARE
#define PRINTIM_HACK_WORKS
#define MEMO_HACK_WORKS

#define MEM_START 0x011ea108 - 0x10000
#define TEXT_START 0x00492150 - 0x10000
#define COPY_LENGTH 0x500000

// Code that writes "PrintIM" to JPEG images. A safe place
// To execute code.
#define FIRMWARE_PRINTIM 0x00516c90
#define MEM_PRINTIM 0x0
#define FIRMWARE_PRINTIM_MAX 236

// Injection details for "voice memo" feature
#define FIRMWARE_MEMO 0x0063fe20
#define MEM_MEMO 0x01397dd8
#define FIRMWARE_MEMO_MAX 100

// Memory address where code can be copied. Need
// A bunch of useless bytes that don't seem important,
// crashes when I go over 2kb
#define MEM_FREE_SPACE 0x00e572e8

// Where to hack on the PTP thumbnail function, 
// Seems to have bytes [0xf0, 0x4d, 0x2d, 0xe9]
#define MEM_PTP_THUMBNAIL 0x00e56fbc

// Dumper temp addr
#define DUMPER_TEMP_ADDR 0x00e56f34

// fujifilm.co.jp text printed by PTP
#define MEM_MODEL_TEXT 0x00e5e228

// "USB" unicode text shown when plugged in
#define MEM_USB_TEXT 0x003276f8

// addr of ".WAV" text used by voice memo
#define MEM_WAV_TEXT 0x0137cea4

// Addresses exposed in memory and in firmware
#define FIRM_DUMP_ADDR 0x006e3748
#define MEM_DUMP_ADDR 0x0143b700

// "Seems to work" screen buffer
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define SCREEN_BUFFER 0x1cee77e + ((SCREEN_WIDTH * SCREEN_HEIGHT) * 0)

#define DEV_FLAG 0x007a0e64

#define FUJI_FOPEN_HANDLER 0x00fd45b4
#define FUJI_FWRITE_HANDLER 0x00fd462c
#define FUJI_FCLOSE_HANDLER 0x00fd45dc

#ifdef STUBS
	#include "stub.h"

	NSTUB(fuji_drive, 0x0072db0c)

	NSTUB(fuji_fopen, 0x0072b87c)
	NSTUB(fuji_fread, 0x0072b618)
	NSTUB(fuji_fwrite, 0x0072b428)
	NSTUB(fuji_fclose, 0x0072b250)

	NSTUB(fuji_malloc, 0x0073a2cc)

	NSTUB(fuji_toggle, 0x00fd5a1c)
	NSTUB(fuji_zero, 0x00fd4590)

	/* Test:
	sqlite_exec(0x0144c67c, "create table foo()", ); 
	*/

	NSTUB(sqlite_parse, 0x01435224) // not entirely sure
	NSTUB(sqlite_exec, 0x014224b4)
	NSTUB(sqlite_snprintf, 0x013ff32c)
	NSTUB(sqlite_malloc, 0x013fddcc) // aka sqlite3Malloc, does not seem to work at all

	NSTUB(random_strcpy, 0x0072f90c) // good emulator testing function
	NSTUB(random_strncat, 0x0072f9d8)

	NSTUB(fuji_screen_write, 0x011d1fb4)
	NSTUB(fuji_discard_text_buffer, 0x011d1f90)

	NSTUB(fuji_ptp_strncpy, 0x00730148)

	NSTUB(ui_get_text, 0x0122e024)

	NSTUB(file_test, 0x00e2e220)
#endif

/*

Container: 
    StandardVersion = 100
    VendorExtensionID = Microsoft
    VendorExtensionVersion = 100
    VendorExtensionDesc = fujifilm.co.jp: 1.0; 
    FunctionalMode = 0
    OperationsSupported = ['GetDeviceInfo', 'OpenSession', 'CloseSession', 'GetStorageIDs', 'GetStorageInfo', 'GetNumObjects', 'GetObjectHandles', 'GetObjectInfo', 'GetObject', 'GetThumb', 'DeleteObject', 'SendObjectInfo', 'SendObject', 'FormatStore', 'GetDevicePropDesc', 'GetDevicePropValue', 'SetDevicePropValue', 'GetPartialObject', 36876, 36877, 36893, 'GetObjectPropsSupported', 'GetObjectPropDesc', 'GetObjectPropValue', 'GetObjPropList']
    EventsSupported = ['ObjectAdded', 'ObjectRemoved', 'StoreAdded', 'StoreRemoved', 'DevicePropChanged', 'DeviceInfoChanged', 'RequestObjectTransfer']
    DevicePropertiesSupported = ['BatteryLevel', 54019, 'SessionInitiatorVendorInfo', 'PerceivedDeviceType']
    CaptureFormats = []
    ImageFormats = ['EXIF_JPEG', 'JFIF']
    Manufacturer = FUJIFILM
    Model = XF1
    DeviceVersion = 1.01

*/
