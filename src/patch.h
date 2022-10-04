// Defines assembly functions in patch files
#ifndef PATCH_H
#define PATCH_H

void _ptp_9805_hack();
int _file_loader();
int _dbg_patch();
uintptr_t bruteForceSearch(uint8_t *bytes, int length);
uintptr_t findFuncHeader(uint32_t addr);

#endif
