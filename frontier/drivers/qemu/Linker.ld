ENTRY(_start)

PHDRS {
	code         PT_LOAD;
	data         PT_LOAD;
}


SECTIONS {
	. = 0x10000;

	. = ALIGN(4);
	.text : {
		_text_start = .;
		*(.text)
		_text_end = .;
	} : data

	. = ALIGN(4);
	.rodata : {
		_rodata_start = .;
		*(.rodata*)
		_rodata_end = .;
	} : data

	. = ALIGN(4);
	.bss : {
		_bss_start = .;
		*(.bss*)
		_bss_end = .;
	}  : data

	. = ALIGN(4);
	.got : {
		_got_start = .;
		*(.got*)
		_got_end = .;
	}  : data

	. = ALIGN(4);
	.data : {
		_data_start = .;
		*(.data*)
		_data_end = .;
	} : data

	/* Embed stack space in the binary: */
	. = ALIGN(8);
	. = . + 0x1000;
	stack_top = .;

	/* The data will be appended */
	_symbol_table_start = .;
}
