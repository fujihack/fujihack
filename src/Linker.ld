/* Daniel's Idiot friendly bare metal ARM linker script */
OUTPUT_ARCH(arm)
ENTRY(_start)

SECTIONS {
	. = 0x10000000;

	.text : { *(.text) }

	. = ALIGN(4);
	.data : { *(.data) }

	. = ALIGN(4);
	.rodata : { *(.rodata) }

	. = ALIGN(4);
	.got : {
		_got_start = .;
		*(.got*)
		_got_end = .;
	}

	. = ALIGN(4);
	_bss_start = .;
	.bss : { *(.bss) }
	_bss_end = .;
}
