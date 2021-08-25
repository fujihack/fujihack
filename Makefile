MODEL ?= xf1
INPUT_FILE ?= ${shell echo ~/Downloads/FPUPDATE-xf1.DAT}
OUTPUT_FILE ?= /media/daniel/disk/FPUPDATE.DAT

# Send makefile flags into cflags
FLAG := -include "model/${MODEL}.h"
FLAG += '-D OUTPUT_FILE="${OUTPUT_FILE}"'
FLAG += '-D INPUT_FILE="${INPUT_FILE}"'
FLAG += '-D MODEL="${MODEL}"'

asm:
	@${CC} ${FLAG} firm.c -o firm
	@./firm asm
	@rm firm

lay:
	@${CC} ${FLAG} firm.c -o firm
	@./firm lay
	@rm firm

pack:
	@${CC} ${FLAG} firm.c -o firm
	@./firm pack
	@rm firm

unpack:
	@${CC} ${FLAG} firm.c -o firm
	@./firm unpack
	@rm firm

clean:
	@rm -rf output* firm *.o *.out *.DAT *.elf