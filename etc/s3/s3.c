// Create motorola S3 File
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// S1 01 00A2 02 5A

enum S3Type {
	S1,
	S2,
	S3,
	S4,
	S5,
	S6,
	S7,
	S8,
	S9
};

struct Tweak {
	int type;
	uintptr_t addr;
	uint8_t *value;
	int value_size;
};

int main() {
	struct Tweak f;
	f.type = S1;
	f.addr = 0x00A2;
	f.value = (char[]){0x2};
	f.value_size = 1;
	
	printf("S1 %X %X ",
		(uint8_t)f.value_size,
		(uint16_t)f.addr
	);
	
	uint32_t checksum = (uint8_t)f.value_size
		+ (uint16_t)f.addr; // should be split by uint8_t
	
	for (int i = 0; i < f.value_size; i++) {
		checksum += f.value[i];
		printf("%X ", f.value[i]);
	}
	
	// get last byte (least significant byte)
	checksum = (uint8_t)(checksum & 0x00FF);
	
	checksum = ~checksum;
	
	printf("%X ", (uint8_t)checksum);
	
	printf("\n");
}
