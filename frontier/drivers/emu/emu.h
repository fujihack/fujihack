#ifndef FIO_H
#define FIO_H

// Write
#define SYS_CTL 0x40000000
#define UART_OUT_CHAR 0x40000001

// Syscall paramters
#define SYS_REGS 0x40000004
#define SYS_R0 0x40000004
#define SYS_R1 0x40000008
#define SYS_R2 0x4000000c

// Read
#define SYS_KEY 0x4000000c
#define SYS_MOUSE_DOWN 0x40000010
#define SYS_MOUSE_X 0x40000014
#define SYS_MOUSE_Y 0x40000018
#define SYS_READ_REGS 0x4000001c
#define SYS_TICKS_MS 0x40000024
#define SYS_GET_CHAR 0x40000028

// System constants
#define SYS_EXIT 0
#define SYS_RENDER 1
#define SYS_BARF 2
#define SYS_SETUP_BMP 3
#define SYS_SLEEP 4
#define SYS_FOPEN 5
#define SYS_FWRITE 6
#define SYS_FREAD 7
#define SYS_FILE_SIZE 8
#define SYS_FCLOSE 9
#define SYS_FSEEK 10
#define SYS_SEGMENT 11

#define SCREEN_BUFFER 0x40000100

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 480

// Address to an integer
#define MEM_ALLOC_START 0x40000008

#endif
