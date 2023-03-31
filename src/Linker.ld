/* Daniel's Idiot friendly bare metal ARM linker script */
OUTPUT_ARCH(arm)
ENTRY(_start)

	 SECTIONS
     {
       . = 0x3e40000;
       .text : { *(.text) }
       .data : { *(.data) }
       .rodata : { *(.rodata) }
       _bss_start = .;
       .bss : { *(.bss) }
       _bss_end = .;
     }
