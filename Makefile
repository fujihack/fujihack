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

# import FIRMWARE_PRINTIM macro from header file
include src/util.mk
$(call importMacro, model/$(model).h, FIRMWARE_PRINTIM, %x)
$(call importMacro, model/$(model).h, FIRMWARE_PRINTIM_MAX, %u)

ARMCC=arm-none-eabi
ARMCFLAGS=-mcpu=cortex-a8 -c --include model/$(model).h

help:
	@echo "Parameters:"
	@echo "  model      Used for camera info, see model/. Can be left blank if you are just unpacking."
	@echo "  input      Input the stock firmware file downloaded from Fujfilm"
	@echo "  output     Where you want the modified FPUPDATE.DAT to go."
	@echo "  temp_file  Where you want to unpacked data to go."
	@echo "Example:"
	@echo "  make unpack input=~/Downloads/FPUPDATE.DAT temp_file=output"

# Use the firm program to send injection into 
inject.o: $(asm_file)
	$(ARMCC)-gcc $(ARMCFLAGS) $(asm_file) -o inject.o
	$(ARMCC)-ld -Bstatic -Ttext=0x$(FIRMWARE_PRINTIM) inject.o -o inject.elf
	$(ARMCC)-objcopy -O binary inject.elf inject.o

inject: firm inject.o
	./firm $@ inject.o 0x$(FIRMWARE_PRINTIM) $(FIRMWARE_PRINTIM_MAX)

asm: unpack inject pack

# Route makefile target into firmware program
firm: firm.c
	$(CC) $(HOST_CFLAGS) firm.c -o firm

pack unpack lay: firm
	./firm $@

clean:
	$(RM) output* firm *.o *.out *.DAT *.elf

.PHONY: pack unpack lay asm clean help
