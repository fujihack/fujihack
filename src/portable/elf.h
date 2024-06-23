// Headers for 32 bit ARM ELF
#include <stdint.h>

#pragma pack(push, 1)

#define ELF_32_BIT 1
#define ELF_64_BIT 2
#define ELF_LITTLE_ENDIAN 1
#define ELF_BIG_ENDIAN 2

#define ELF_MACHINE_ARM 0x28

#define ELF_RELOCATABLE 1
#define ELF_EXECUTABLE 2
#define ELF_SHARED 3
#define ELF_CORE 4

#define SHT_PROGBITS 1
#define SHT_NOBITS 8
#define SHT_REL 9

#define PT_NULL 0
#define PT_LOAD 1
#define PT_DYNAMIC 2
#define PT_INTERP 3

#define ELF_MAGIC 0x464C457F

#define SHN_UNDEF 0
#define SHN_LOPROC 0xFF00
#define SHN_HIPROC 0xFF1F
#define SHN_LOOS 0xFF20
#define SHN_HIOS 0xFF3F
#define SHN_ABS 0xFFF1
#define SHN_COMMON 0xFFF2

#define R_ARM_NONE        0
#define R_ARM_PC24        1
#define R_ARM_ABS32       2
#define R_ARM_REL32       3
#define R_ARM_THM_CALL      10
#define R_ARM_CALL        28
#define R_ARM_JUMP24      29
#define R_ARM_THM_JUMP24    30
#define R_ARM_TARGET1       38
#define R_ARM_V4BX        40
#define R_ARM TARGET2       41
#define R_ARM_PREL31      42
#define R_ARM_MOVW_ABS_NC     43
#define R_ARM_MOVT_ABS      44
#define R_ARM_THM_MOVW_ABS_NC   47
#define R_ARM_THM_MOVT_ABS    48

struct ElfProgHeader32 {
	uint32_t type;
	uint32_t offset;
	uint32_t vaddr;
	uint32_t paddr;
	uint32_t filesz;
	uint32_t memsz;
	uint32_t flags;
	uint32_t align;
};

struct ElfSectHeader32 {
	uint32_t name;
	uint32_t type;
	uint32_t flags;
	uint32_t addr;
	uint32_t offset;
	uint32_t size;
	uint32_t link;
	uint32_t info;
	uint32_t addralign;
	uint32_t entsize;
};

struct ElfHeader32 {
	uint32_t magic;
	uint8_t bits;
	uint8_t endian;
	uint8_t version;
	uint8_t abi;
	uint8_t abi2;
	uint8_t padding[7];
	uint16_t type;
	uint16_t machine;
	uint32_t version2;
	uint32_t entry; // code entry offset
	uint32_t phoff;
	uint32_t shoff;
	uint32_t flags;
	uint16_t ehsize; // size of this header
	uint16_t phentsize; // size of program header table entry
	uint16_t phnum; // number of entries in program header table
	uint16_t shentsize; // size of header section table entry
	uint16_t shnum; // number of entries in the section header table
	uint16_t shstrndx;
};

struct ElfSym32 {
	uint32_t name;
	uint32_t value;
	uint32_t size;
	uint8_t info;
	uint8_t other;
	uint16_t shndx;
};

struct ElfRel32 {
	uint32_t offset;
	uint32_t info;
};

#pragma pack(pop)
