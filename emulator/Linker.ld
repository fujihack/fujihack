OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)

SECTIONS {
	. = ALIGN(4);
	.rel.dyn : {
		*(.rel.dyn)
	}

	. = ALIGN(4);
	.rodata : {
		*(.rodata*)
	}

	. = ALIGN(4);
	.data : {
		DATA_START = .;
		*(.data*)
		DATA_END = .;
	}
}

