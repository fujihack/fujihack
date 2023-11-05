/* Daniel's Idiot friendly bare metal ARM linker script */
OUTPUT_ARCH(arm)
ENTRY(_start)

PHDRS {
	code         PT_LOAD;
	data         PT_LOAD;
}

INCLUDE extern.ld

SECTIONS {
	. = 4096;

	/* Stores code and stuff */
	. = ALIGN(4);
	.text : {
		_text_start = .;
		*(.text)
		_text_end = .;
	} : data

	/* Read only data, stores strings and stuff */
	. = ALIGN(4);
	.rodata : {
		_rodata_start = .;
		*(.rodata*)
		_rodata_end = .;
	} : data

	/* Block starting symbol, for unitialized global arrays */
	. = ALIGN(4);
	.bss : {
		_bss_start = .;
		*(.bss*)
		_bss_end = .;
	}  : data

	/* Global offset table. To add the correct offset, use this code:
		uint32_t got_start = _got_start;
		uint32_t got_end = _got_end;
		int32_t len = (got_end - got_start) / 4 - 1;
		for (int i = 0; i < len; i++) {
			((uint32_t*)((uint32_t)got_start + (uint32_t)base))[i] += base;
		}
	*/
	. = ALIGN(4);
	.got : {
		_got_start = .;
		*(.got*)
		_got_end = .;
	}  : data

	/* Regular data */
	. = ALIGN(4);
	.data : {
		_data_start = .;
		*(.data*)
		_data_end = .;
	} : data

	/* The data will be appended */
	_symbol_table_start = .;
}
