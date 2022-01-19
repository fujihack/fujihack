# Defaults, tweak these via CLI
model?=xf1
input?=$(shell echo ~/Downloads/FPUPDATE.DAT)
output?=FPUPDATE.DAT
temp_file?=output
asm_file?=main.S

# Include model info by default
HOST_CFLAGS=-include "model/$(model).h"

# Send makefile flags into cflags
HOST_CFLAGS+='-D OUTPUT_FILE="$(output)"'
HOST_CFLAGS+='-D INPUT_FILE="$(input)"'
HOST_CFLAGS+='-D MODEL="$(model)"'
HOST_CFLAGS+='-D TEMP_FILE="$(temp_file)"'
HOST_CFLAGS+='-D ASM_FILE="$(asm_file)"'

help:
	@echo "Parameters:"
	@echo "  model      Used for camera info, see model/. Can be left blank if you are just unpacking."
	@echo "  input      Input the stock firmware file downloaded from Fujfilm"
	@echo "  output     Where you want the modified FPUPDATE.DAT to go."
	@echo "  temp_file  Where you want to unpacked data to go."
	@echo "Example:"
	@echo "  make unpack input=~/Downloads/FPUPDATE.DAT temp_file=output"

pack unpack lay asm:
	$(CC) $(HOST_CFLAGS) firm.c -o firm
	./firm $@

clean:
	$(RM) output* firm *.o *.out *.DAT *.elf

.PHONY: pack unpack lay asm clean help
