# Makefile for Fujihack
TOPL=../
-include ../config.mak
include ../Makefile

HACK_BIN_DEPS=boot.o stub.o file.o main.o sys.o mem.o io.o screen.o remap.o video.o dump.o
HACK_BIN_DEPS+=$(addprefix portable/,asm.o bmp.o ui.o loader.o sym.o error.o ml.o app.o)

ARMCFLAGS+=-Iportable/

ARMCFLAGS+=-include ../model/$(model).h -c -marm -O0 -I$(TOPL)/src -mcpu=cortex-a5 -fpic -mapcs-frame -mabi=aapcs
ARMLDFLAGS+=-T Linker.ld $(WRAPS) -lc -lgcc -lm

# Remove unused sections/functions/variables
# This helps cut down on size a LOT
#ARMCFLAGS+=-fdata-sections -ffunction-sections
#ARMLDFLAGS+=--gc-sections

copy: hack.bin
	$(TOPL)/ptp/fuji -s hack.bin

clean-all:
	$(RM) $(HACK_BIN_DEPS)

hack.bin: $(HACK_BIN_DEPS) build-frontier
	$(ARMCC)-ld $(HACK_BIN_DEPS) $(ARMLDFLAGS) -lc -lgcc -o hack.elf
	$(ARMCC)-objcopy -O binary hack.elf hack.bin
	$(TOPL)/frontier/tool/frontier.o -i hack.elf -o hack.bin -s
	$(ARMCC)-size --format=berkeley --target=binary hack.bin

# Compiling rules are defined in ../Makefile
