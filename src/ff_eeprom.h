// Fujifilm EEPROM stubs (generally very similar across devices)
#ifndef FF_EEPROM_H
#define FF_EEPROM_H

// ID in the header file
#define EEP_MODEL_NUMBER 0x11b

// 4 byte string, the expected filename for the firmware update
#define EEP_FIRM_NUM 0x1c0

#define EEP_BOOTLOADER_PID 0x13a
#define EEP_PTP_PID 0x13e

// "X-A2"
#define EEP_MODEL_NAME 0x15c

// Should be 'FUJIFILM'
#define EEP_VENDOR 0x16f

#define GET_EEP(x) ((uint8_t*)MEM_EEP_START)[x]
#define SET_EEP(x, v) ((uint8_t*)MEM_EEP_START)[x] = (uint8_t)v

// Found in 'EEPRom setting menu' code
void fuji_apply_eeprom();

#endif
