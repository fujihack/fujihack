include etc/util.mk
-include config.mak

# Defaults, tweak these via CLI or config.mak
model?=xf1
input?=$(shell echo ~/Downloads/FPUPDATE.DAT)
output?=FPUPDATE.DAT
temp_file?=output
asm_file?=main.S

# Include model info by default
HOST_CFLAGS=-include "model/$(model).h" -D "MODEL=\"$(model)\""
ARMCC?=arm-none-eabi
ARMCFLAGS?=-mcpu=cortex-a8 -c --include model/$(model).h

help:
	@echo "Parameters:"
	@echo "  model      Used for camera info, see model/. Can be left blank if you are just unpacking."
	@echo "  input      Input the stock firmware file downloaded from Fujfilm"
	@echo "  output     Where you want the modified FPUPDATE.DAT to go."
	@echo "  temp_file  Where you want to unpacked data to go."
	@echo "Example:"
	@echo "  make unpack input=~/Downloads/FPUPDATE.DAT temp_file=output"

# Use the firm program to send injection into 
inject.bin: $(asm_file)
	$(ARMCC)-gcc $(ARMCFLAGS) $(asm_file) -o inject.o
	$(ARMCC)-ld -Bstatic inject.o -o inject.elf
	$(ARMCC)-objcopy -O binary inject.elf inject.bin

inject: firm inject.bin
	# Import macros
	$(call importMacro, model/$(model).h, MEM_PRINTIM, %x, MEM_INJECT_ADDR)
	$(call importMacro, model/$(model).h, FIRMWARE_PRINTIM, %x, FIRMWARE_INJECT_ADDR)
	$(call importMacro, model/$(model).h, FIRMWARE_PRINTIM_MAX, %u, FIRMWARE_INJECT_MAX)

	./firm $@ -j inject.bin -a 0x$(FIRMWARE_INJECT_ADDR) -x $(FIRMWARE_INJECT_MAX)

asm: unpack inject pack

pack unpack lay: firm
	./firm $@ -m $(model) -i $(input) -o $(output) -t $(temp_file)

# Route makefile target into firmware program
firm: firm.c
	$(CC) $(HOST_CFLAGS) firm.c -o firm

upload_ptp:
	python3 ptp/firmware.py $(output)

# Force compilation of firm every time. The compiled binary
# is model specific.
.PHONY: firm

clean:
	$(RM) output* firm *.o *.out *.DAT *.elf *.bin

.PHONY: pack unpack lay asm clean help inject upload_ptp
