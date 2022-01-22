OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)

ENTRY(_start)

SECTIONS {
	.text 0x20f10e8: {
		*(.text)
	}
}
