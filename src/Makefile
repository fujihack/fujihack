# Makefile for Fujihack + Frontier
TOPL=../
-include ../config.mak
include ../Makefile

FRONTIER=$(TOPL)frontier
FRONTIER_CORE=$(FRONTIER)/src/
FRONTIER_JS=$(FRONTIER)/mjs/

HACK_BIN_DEPS=boot.o stub.o file.o main.o sys.o mem.o io.o screen.o remap.o video.o
HACK_BIN_DEPS+=$(addprefix $(FRONTIER_CORE),asm.o bmp.o ui.o)
#HACK_BIN_DEPS+=$(addprefix $(FRONTIER_JS),mjs.o)

ARMCFLAGS+=-I$(FRONTIER_JS)

#WRAPS=--wrap=_malloc_r

ARMCFLAGS+=-include ../model/$(model).h -c -marm -O0 -I$(TOPL)/src -mcpu=cortex-a5 -fpic -mapcs-frame
ARMLDFLAGS+=-T Linker.ld $(WRAPS) -lc -lgcc -lm

ARMCFLAGS+=-I$(FRONTIER_CORE) -DCS_PLATFORM=0

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
	$(TOPL)/frontier/emulator/frontier.o -i hack.elf -o hack.bin -s
	$(ARMCC)-size --format=berkeley --target=binary hack.bin

# Compiling rules are defined in ../Makefile
