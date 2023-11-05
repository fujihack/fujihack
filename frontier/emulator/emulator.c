#include <sys/time.h>
#include <sys/stat.h>
#include <unicorn/unicorn.h>
#include <fcntl.h>

#include <emu.h>
#include <bmp.h>
#include <emulator.h>

#define E_STACK_SIZE 1000000
#define E_RAM (16 * 1024 * 1024)
#define E_ADDRESS 4096
#define E_SCREEN_OF 0x100

uint32_t alloc_start = 0;
uint32_t seg_start = 0;
uint32_t seg_length = 0;
uint8_t already_dumped = 0;

struct Keys keys;

struct IOLastRegs {
	uint32_t r0;
	uint32_t r1;
	uint32_t r2;
}io_regs;

void barf(uc_engine *uc) {
	int reg;

	uc_reg_read(uc, UC_ARM_REG_PC, &reg);
	printf("PC: %08X\n", reg);
	char buffer[512];
	sprintf(buffer, "arm-none-eabi-addr2line -e %s %X", "os.elf", (uint32_t)reg);
	int err = system(buffer);
	if (err) {
		puts("addr2line err");
	}

	uint32_t intbuf;
	uc_mem_read(uc, reg, &intbuf, 4);
	printf("val: %X\n", intbuf);

	puts("from");

	uc_reg_read(uc, UC_ARM_REG_LR, &reg);
	printf("LR: %08X\n", reg);
	sprintf(buffer, "arm-none-eabi-addr2line -e %s %X", "os.elf", (uint32_t)reg);
	err = system(buffer);
	if (err) {
		puts("addr2line err");
	}

	for (int i = 0; i < 10; i++) {
		uc_reg_read(uc, UC_ARM_REG_R0 + i, &reg);
		printf("r%d: 0x%X\n", i, reg);
	}

	if (!already_dumped) {
		puts("Dumping..");
		void *buf = malloc(E_RAM);
		uc_mem_read(uc, E_ADDRESS, buf, E_RAM);
		FILE *f = fopen("dump", "w");
		if (f == NULL) return;
		fwrite(buf, 1, E_RAM, f);
		fclose(f);
		free(buf);
		already_dumped = 1;
	}
}

uint64_t mmio_reads(uc_engine *uc, uint64_t offset, unsigned size, void *user_data) {
	switch (offset) {
	case 8:
		return alloc_start;
	case 0xc:
		bmp_handle_input();
		return keys.last_key;
	case 0x10:
		bmp_handle_input();
		return keys.mouse_down;
	case 0x14:
		bmp_handle_input();
		return keys.mouse_x;
	case 0x18:
		bmp_handle_input();
		return keys.mouse_y;
	case 0x1c:
		return io_regs.r0;
	case 0x20:
	case 0x24: {
		struct timeval  tp;
		struct timezone tzp;
		gettimeofday(&tp, &tzp);
		return (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
		}
	case 0x28:
		return getchar();
	}

	return 0x0;
}

void mem_get_string(uc_engine *uc, int of, char *string, int max) {
	char buf[1];
	int i = 0;
	while (1) {
		uc_mem_read(uc, of, buf, 1);
		string[i] = buf[0];
		i++;
		if (buf[0] == 0) {
			return;
		}
		of++;
	}
}

void mmio_syscall(uc_engine *uc, int value) {
	if (value == SYS_EXIT) {
		printf("Return: %08X\n", io_regs.r0);

		uc_close(uc);
		exit(0);
	} else if (value == SYS_RENDER) {
		bmp_render();
	} else if (value == SYS_BARF) {
		barf(uc);
	} else if (value == SYS_SETUP_BMP) {
		bmp_setup();
	} else if (value == SYS_SLEEP) {
		usleep(io_regs.r0 * 1000);
	} else if (value == SYS_FOPEN) {
		if (io_regs.r1 == 0x10000) {
			io_regs.r1 = 0x8000;
		}
	
		char filename[64];
		mem_get_string(uc, io_regs.r0, filename, sizeof(filename));
		io_regs.r0 = open(filename, io_regs.r1, io_regs.r2);
	} else if (value == SYS_FWRITE) {
		char *buffer = malloc(io_regs.r1);
		uc_mem_read(uc, io_regs.r1, buffer, io_regs.r2);
		io_regs.r0 = write(io_regs.r0, buffer, io_regs.r1);
	} else if (value == SYS_FILE_SIZE) {
		char path[64];
		mem_get_string(uc, io_regs.r0, path, sizeof(path));
		struct stat s;
		stat(path, &s);
		io_regs.r0 = s.st_size;
	} else if (value == SYS_FREAD) {
		char *buffer = malloc(io_regs.r2);
		ssize_t x = read(io_regs.r0, buffer, io_regs.r2);
		uc_mem_write(uc, io_regs.r1, buffer, io_regs.r2);
		free(buffer);
		io_regs.r0 = x;
	} else if (value == SYS_FCLOSE) {
		io_regs.r0 = close(io_regs.r0);
	} else if (value == SYS_FSEEK) {
		io_regs.r0 = lseek(io_regs.r0, (off_t)io_regs.r1, io_regs.r2);
	} else if (value == SYS_SEGMENT) {
		seg_start = io_regs.r0;
		seg_length = io_regs.r1;
	}
}

void mmio_writes(uc_engine *uc, uint64_t offset, unsigned size, uint64_t value, void *user_data) {
	if (offset >= E_SCREEN_OF && offset <= E_SCREEN_OF + (SCREEN_WIDTH * SCREEN_HEIGHT * 4)) {
		screen[(offset - 0x100) / 4] = (uint32_t)value;
		return;
	}

	switch (offset) {
	case 0:
		mmio_syscall(uc, value);
		break;
	case 1:
		putchar(value);
		break;
	case 4:
		io_regs.r0 = value;
		break;
	case 8:
		io_regs.r1 = value;
		break;
	case 12:
		io_regs.r2 = value;
		break;
	}
}

void invalid_write(uc_engine *uc, uint64_t offset, unsigned size, uint64_t value, void *user_data) {
	printf("Invalid write addr:%lX value:%lX\n", offset, value);
	barf(uc);
	exit(1);
}

int emulator(char *filename) {
	uc_engine *uc;
	uc_err err;

	err = uc_open(UC_ARCH_ARM, UC_MODE_ARM, &uc);
	if (err != UC_ERR_OK) {
		printf("Failed\n");
		return 1;
	}

	// Map dedicated RAM
	err = uc_mem_map(uc, E_ADDRESS, E_RAM, UC_PROT_ALL);
	if (err != UC_ERR_OK) {
		printf("Failed to map memory\n");
		return 1;
	}

	FILE *f = fopen(filename, "rb");
	if (f == NULL) {
		printf("Can't open %s\n", filename);
		return 1;
	}

	fseek(f, 0, SEEK_END);
	int length = ftell(f);
	fseek(f, 0, SEEK_SET);
	char *buffer = malloc(length);
	int rc = fread(buffer, length, 1, f);
	if (rc == 0) {
		return 1;
	}
	fclose(f);

	err = uc_mem_write(uc, E_ADDRESS, buffer, length);
	free(buffer);
	if (err != UC_ERR_OK) {
		printf("Failed to write data\n");
		return 1;
	}

	// 100k of stack (grows backwards)
	int reg = E_ADDRESS + length + E_STACK_SIZE;
	reg -= (reg % 0x8);
	uc_reg_write(uc, UC_ARM_REG_SP, &reg);

	// Align allocation start address
	alloc_start = reg + 0x100;
	alloc_start -= (reg % 0x8);

	// Set up IO regions
	err = uc_mmio_map(uc, 0x40000000, 4096 * 1000, mmio_reads, NULL,
		mmio_writes, NULL);
	if (err != UC_ERR_OK) {
		puts("MMIO map error 0x4*-0x5*");
		return 1;
	}

	err = uc_mmio_map(uc, 0x0, E_ADDRESS, NULL, NULL, invalid_write, NULL);
	if (err != UC_ERR_OK) {
		puts("MMIO map failure");
		return 1;
	}

	err = uc_emu_start(uc, E_ADDRESS, E_RAM + E_ADDRESS, 0, 0);
	if (err) {
		printf("Emulation failed: %u %s\n", err, uc_strerror(err));
		barf(uc);
	} else {
		barf(uc);
		puts("Success");
	}
	
	uc_close(uc);

	return 0;
}
