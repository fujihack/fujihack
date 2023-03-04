TOPL=../
-include ../config.mak
include ../Makefile

# Target specific dependencies
HACK_BIN_DEPS=boot.o main.o lib.o stub.o hijack.o screen.o io.o util.o rust.o 

ARMCFLAGS?=-fpack-struct -fpic -mcpu=cortex-a5 -include ../model/$(model).h -c -marm -mapcs-frame -O2
ARMLDFLAGS?=--gc-sections -Bstatic -T Linker.ld

# Remove unused sections/functions/variables
# This helps cut down on size a LOT
ARMCFLAGS+=-fdata-sections -ffunction-sections
ARMLDFLAGS+=--gc-sections

hack.bin: $(HACK_BIN_DEPS)
	$(ARMCC)-ld $(ARMLDFLAGS) $(HACK_BIN_DEPS) -o hack.elf
	$(ARMCC)-objcopy -O binary hack.elf hack.bin
	$(ARMCC)-size --format=berkeley --target=binary hack.bin

font.bin: font/font.h
	$(ARMCC)-gcc -c font/font.c -o font.o
	$(ARMCC)-objcopy -O binary font.o font.bin

# Compiling rules are defined in ../Makefile
