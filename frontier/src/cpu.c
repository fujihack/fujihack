// Use mrc instruction to extract information from register
// Copyright (C) 2022-2023 Frontier by Daniel C - Apache License
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <sys.h>

#define REGBITS(i, a, b) ((i & ((1u << (a + 1)) - 1)) >> b)

void log_cpu_info(uint32_t i) {
	sys_debug("Logging CPU info\n");
	char *impl_str;
	switch ((char)REGBITS(i, 30, 24)) {
	case 'A':
		impl_str = "ARM Limited";
		break;
	case 'D':
		impl_str = "Digital Equipment Corporation";
		break;
	case 'M':
		impl_str = "Motorola - Freescale Semiconductor Inc.";
		break;
	case 'V':
		impl_str = "Marvell Semiconductor Inc.";
		break;
	case 'i':
		impl_str = "Intel Corporation";
		break;
	default:
		impl_str = "Reserved by ARM Limited";
	}

	char *arch_str;
	switch (REGBITS(i, 19, 16)) {
	case 0x0:
		arch_str = "ARMv1";
		break;
	case 0x1:
		arch_str = "ARMv2";
		break;
	case 0x2:
		arch_str = "ARMv3";
		break;
	case 0x3:
		arch_str = "ARMv4";
		break;
	case 0x4:
		arch_str = "ARMv4T";
		break;
	case 0x5:
		arch_str = "ARMv5";
		break;
	case 0x6:
		arch_str = "ARMv5T";
		break;
	case 0x7:
		arch_str = "ARMv5TE";
		break;
	case 0x8:
		arch_str = "ARMv5TEJ";
		break;
	case 0x9:
		arch_str = "ARMv6";
		break;
	case 0xA:
		arch_str = "ARMv6K";
		break;
	case 0xB:
		arch_str = "ARMv6T2";
		break;
	case 0xC:
		arch_str = "ARMv6Z";
		break;
	case 0xD:
		arch_str = "ARMv6KZ";
		break;
	case 0xE:
		arch_str = "ARMv7";
		break;
	default:
		arch_str = "Custom/Reserved";
		break;
	}

	sys_debug("Impl: %s\n", impl_str);
	sys_debug("Arch: %s\n", arch_str);

	sys_debug("Part number: %lX\n", REGBITS(i, 15, 4));
	sys_debug("Revision: %lX\n", REGBITS(i, 3, 0));
}

uint32_t asm_get_cpuinfo(void) {
	uint32_t i;
	__asm__("mrc p15, 0x0, %0, c0, c0, 0x0\n" : "=r" (i));
	return i;
}
