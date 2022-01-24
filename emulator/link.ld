OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)

ENTRY(_start)

SECTIONS {
	.text : {
		*(.text)
	}

	.got : {
		*(.got)
	}
}
