MODEL ?= hs20exr
INPUT_FILE ?= ~/Downloads/FPUPDATE.DAT
OUTPUT_FILE ?= FPUPDATE.DAT

# Send makefile flags into cflags
FLAG := -include "${MODEL}.h"
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