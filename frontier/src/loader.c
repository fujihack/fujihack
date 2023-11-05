// Copyright (C) 2022-2023 Frontier by Daniel C - Apache License
// Frontier 32 bit ELF Loader
// This will perform a basic parsing of a standard ELF file, for 32-bit ARM assembly.
// Most relocation types are supported, although there may be edge cases where this loader
// will fail.

/*
TODO: This doesn't seem to work with .LANCHOR
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys.h>
#include <elf.h>
#include <asm.h>
#include <loader.h>

struct ElfSectHeader32 *get_elf_head(void *file, uint32_t i) {
	struct ElfHeader32 *h = (struct ElfHeader32 *)file;
	return (struct ElfSectHeader32 *)(file + h->shoff + (i * h->shentsize));
}

char *elf_head_name(void *file, uint32_t i) {
	struct ElfHeader32 *h = (struct ElfHeader32 *)file;
	struct ElfSectHeader32 *names = (struct ElfSectHeader32 *)
		(file + h->shoff + (h->shstrndx * h->shentsize));
	return (char *)file + names->offset + i;
}

// Link all symbols in a section
int loader_relocate(void *file, struct ElfFileInfo *info, struct ElfSectHeader32 *s) {
	// To relocation list (.rel.text)
	struct ElfSectHeader32 *l = get_elf_head(file, s->link);

	// To target (text)
	struct ElfSectHeader32 *target = get_elf_head(file, s->info);

	// To symtab
	struct ElfSym32 *syms = (struct ElfSym32 *)(file + l->offset);

	// To strtab
	struct ElfSectHeader32 *str = get_elf_head(file, l->link);

	// Perform the relocations
	struct ElfRel32 *relocs = (struct ElfRel32 *)(file + s->offset);
	for (int i = 0; i < s->size / s->entsize; i++) {
		int index = relocs[i].info >> 8;
		int type = (uint8_t)(relocs[i].info);

		char *name = (char *)(file + str->offset + syms[index].name);
		uint32_t *target_loc = (void *)(file + target->offset + relocs[i].offset);

		// Allocate NOBITS sections only once, switch to PROGBITS
		struct ElfSectHeader32 *reloc_sect = get_elf_head(file, syms[index].shndx);
		if (reloc_sect->type == SHT_NOBITS) {
			if (reloc_sect->size > 0 && s->addr == 0) {
				//puts("Allocating space in BSS");
				reloc_sect->offset = (uint32_t)malloc(reloc_sect->size);
				memset(file + reloc_sect->offset, 0, reloc_sect->size);
				reloc_sect->type = SHT_PROGBITS;
			}
		}
		
		switch (type) {
		case R_ARM_CALL:
			if (syms[index].value == 0 && syms[index].shndx == 0) {
				void *call = ml_sym(name);
				if (call == NULL) call = sym(name);
				if (call == NULL) {
					sys_debug("ELF: Undefined sym %s\n", name);
					sys_report_err("Couldn't find symbol: %s\n", name);
					return 1;
				}
				asm_gen_call(target_loc, call, target_loc);
			} else {
				asm_gen_call(target_loc, file + syms[index].value + get_elf_head(file, syms[index].shndx)->offset, target_loc);
			} break;
		case R_ARM_ABS32:
			*target_loc += (uintptr_t)file + syms[index].value + get_elf_head(file, syms[index].shndx)->offset;
			break;
		case R_ARM_REL32:
			*target_loc += (get_elf_head(file, syms[index].shndx)->offset) - (target->offset + relocs[i].offset);
			break;
		case R_ARM_MOVW_ABS_NC:
		case R_ARM_MOVT_ABS: {
			uintptr_t offset = 0;
			// Allocate common undefined (like BSS)
			if (syms[index].shndx >= SHN_LOPROC) {
				// TODO: Fix this hack
				// (I completely forgot what this was about, something about external data (that didn't exist) being referenced?
				// Or was it a hack for what probably is a BSS section?)
				if (syms[index].shndx == SHN_COMMON && syms[index].value < 100) {
					syms[index].value = (uint32_t)malloc(syms[index].size);
					memset((void *)syms[index].value, 0, syms[index].size);
				}

				offset = syms[index].value;
			} else {
				offset = (uintptr_t)file + syms[index].value + (get_elf_head(file, syms[index].shndx)->offset);
			}

			if (type == R_ARM_MOVT_ABS) {
				offset >>= 16;
			}

			// TODO: instruction to generate movw/movt
			// Although this seems to work OK
			*target_loc &= 0xfff0f000;
			*target_loc |= ((offset & 0xf000) << 4) | (offset & 0x0fff);
			} break;
		}
	}

	return 0;
}

int loader_init_elf(void *file, struct ElfFileInfo *info) {
	memset(info, 0, sizeof(struct ElfFileInfo));

	struct ElfHeader32 *h = (struct ElfHeader32 *)file;

	if (h->magic != ELF_MAGIC) {
		sys_report_err("File provided is not ELF.");
		return 1;
	}

	if (h->bits != ELF_32_BIT || h->machine != ELF_MACHINE_ARM
			|| h->endian != ELF_LITTLE_ENDIAN) {
		sys_report_err("File is not compatible.");
		return 1;
	}

	struct ElfSectHeader32 *names = (struct ElfSectHeader32 *)
				(file + h->shoff + (h->shstrndx * h->shentsize));

	for (int i = 0; i < h->shnum; i++) {
		struct ElfSectHeader32 *s = (struct ElfSectHeader32 *)
			(file + h->shoff + (i * h->shentsize));

		char *sect_name = (char *)file + names->offset + s->name;

		if (s->type == SHT_PROGBITS) {
			info->max_exec_size += s->size;
		} else if (s->type == SHT_REL) {
			if (loader_relocate(file, info, s)) {
				return 1;
			}
		}

		uint32_t of = h->shoff + (i * h->shentsize);

		if (!strcmp(sect_name, ".symtab")) {
			info->symtab_of = of;
		} else if (!strcmp(sect_name, ".strtab")) {
			info->strtab_of = of;
		}
	}

	return 0;
}

// Scan symbols and add them to the global symbol manager (sym.c)
uintptr_t loader_scan_symbols(void *file, struct ElfFileInfo *info) {
	struct ElfSectHeader32 *symtab = (struct ElfSectHeader32 *)(file + info->symtab_of);
	struct ElfSectHeader32 *strtab = (struct ElfSectHeader32 *)(file + info->strtab_of);

	int length = symtab->size / symtab->entsize;

	for (int i = 0; i < length; i++) {
		struct ElfSym32 *sym = (struct ElfSym32 *)(file + symtab->offset + (sizeof(struct ElfSym32) * i));
		if (sym->name != 0) {
			char *curr = (char *)file + strtab->offset + sym->name;
			if (!strcmp(curr, "main") || !strcmp(curr, "panic")) continue;
			if (sym->shndx != 0 && sym->size != 0) {
				struct ElfSectHeader32 *l = get_elf_head(file, sym->shndx);
				sys_debug("Adding new symbol %s\n", curr);
				sym_new(curr, file + l->offset + sym->value);
			}
		}
	}

	return 0;
}

uintptr_t loader_get_symbol(void *file, struct ElfFileInfo *info, char *name) {
	struct ElfSectHeader32 *symtab = (struct ElfSectHeader32 *)(file + info->symtab_of);
	struct ElfSectHeader32 *strtab = (struct ElfSectHeader32 *)(file + info->strtab_of);

	int length = symtab->size / symtab->entsize;

	for (int i = 0; i < length; i++) {
		struct ElfSym32 *sym = (struct ElfSym32 *)(file + symtab->offset + (sizeof(struct ElfSym32) * i));
		if (sym->name != 0) {
			char *curr = (char *)file + strtab->offset + sym->name;
			if (sym->shndx != 0) {
				if (!strcmp(name, curr)) {
					struct ElfSectHeader32 *l = get_elf_head(file, sym->shndx);
					return l->offset + sym->value;
				}
			}
		}
	}

	return 0;
}

// Push all registers and call a void(void) function - mostly for firmware hacks where
// stack manipulation and smashing could happen. Might be a good idea to do this to BL calls to.
int safe_func_exec(void *addr) {
	asm volatile(
		"push {r0-r12}"
	);

	typedef int func(void);
	func* entry = (func*)(addr);
	int rc = entry();	

	asm volatile(
		"pop {r0-r12}"
	);

	return rc;
}

uint32_t loader_exec(void *file, struct ElfFileInfo *info) {
	uintptr_t main = loader_get_symbol(file, info, "main");
	if (main == 0) {
		sys_debug("main() not found\n");
		return 1;
	}

	sys_debug("Calling main...\n");
	int rc = safe_func_exec(file + main);
	sys_report_err("main() return code: %X", rc);
	return rc;
}
