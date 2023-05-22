// Fujifilm EEPROM stubs (generally very similar across devices)
#ifndef FF_EEPROM_H
#define FF_EEPROM_H

// 4 byte string, the expected filename for the firmware update
#define EEP_FIRM_NUM 0x1c0

#define EEP_BOOTLOADER_PID 0x13a
#define EEP_PTP_PID 0x13e

// We should be nice when there isn't much defined in model header file
#ifdef MEM_EEP_START
	#define GET_EEP(x) ((uint8_t*)MEM_EEP_START)[x]
	#define SET_EEP(x, v) ((uint8_t*)MEM_EEP_START)[x] = (uint8_t)v
#else
	#define GET_EEP(x) /* */
	#define SET_EEP(x) /* */
#endif

// Found in 'EEPRom setting menu' code
void fuji_apply_eeprom();

#endif
