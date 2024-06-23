// Frontier Kernel API
#ifndef F_H
#define F_H
#include <stdint.h>

// 0 if unsupported or unknown
extern int sys_mem_in_use;
extern int sys_mem_available;

// Dump registers and memory
void sys_dump();

void sys_debug(const char *format, ...);

void sys_init_bmp();
void sys_init_mem();
int sys_init_syms();

// TODO: Rename to debug_ or log_
void uart_char(char c);
void uart_str(char *string);
void uart_log(char *format, ...);

// TODO: Convert to standard ASCII codes?
#define SYS_BUTTON_NONE 0
#define SYS_BUTTON_QUIT 1
#define SYS_BUTTON_UP 2
#define SYS_BUTTON_DOWN 3
#define SYS_BUTTON_LEFT 4
#define SYS_BUTTON_RIGHT 5
#define SYS_BUTTON_OK 6

void sys_report_err(const char* format, ...);
char *sys_get_error();

// Check if a button is active at a certain point
int sys_check_mouse();
int sys_check_key(int key);

void msleep(int ms);

// Global symbol manager (dlsym equivelant)
void *sym(const char *name);
int sym_new(char *name, uint32_t value);

// Get Magic Lantern compatible symbol (standard baked-in functionality)
void *ml_sym(char *name);

// Load relocatable ELF file into global symbol table
int sys_load_app(char *filename);

#endif
