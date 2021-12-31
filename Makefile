MODEL?=xf1
INPUT_FILE?=$(shell echo ~/Downloads/FPUPDATE-xf1.DAT)
OUTPUT_FILE?= /media/daniel/disk/FPUPDATE.DAT

# Send makefile flags into cflags
CFLAGS=-include "model/$(MODEL).h"
CFLAGS+='-D OUTPUT_FILE="$(OUTPUT_FILE)"'
CFLAGS+='-D INPUT_FILE="$(INPUT_FILE)"'
CFLAGS+='-D MODEL="$(MODEL)"'

# TODO: asm is built in makefile

firm.o: firm.c
	@$(CC) $(FLAG) $< -o $@

pack unpack lay asm: firm.o
	@./firm.o $@

clean:
	rm -rf output* firm *.o *.out *.DAT *.elf
