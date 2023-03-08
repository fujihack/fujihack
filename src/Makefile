TOPL=../
-include ../config.mak
include ../Makefile

FRONTIER=$(TOPL)frontier
FRONTIER_CORE=$(FRONTIER)/core/
FRONTIER_JS=$(FRONTIER)/mjs/

HACK_BIN_DEPS=boot.o stub.o file.o main.o sys.o mem.o
HACK_BIN_DEPS+=$(addprefix $(FRONTIER_CORE),asm.o)
HACK_BIN_DEPS+=$(addprefix $(FRONTIER_JS),mjs.o)

WRAPS=--wrap=_malloc_r

ARMCFLAGS+=-fpic -mcpu=cortex-a7 -include ../model/$(model).h -c -marm -O2
ARMLDFLAGS+=-Bstatic -T Linker.ld $(WRAPS)

ARMCFLAGS+=-I$(FRONTIER_CORE) -DCS_PLATFORM=0

# Remove unused sections/functions/variables
# This helps cut down on size a LOT
#ARMCFLAGS+=-fdata-sections -ffunction-sections
#ARMLDFLAGS+=--gc-sections

hack.bin: $(HACK_BIN_DEPS)
	$(ARMCC)-ld $(HACK_BIN_DEPS) $(ARMLDFLAGS) -lc -lgcc -o hack.elf
	$(ARMCC)-objcopy -O binary hack.elf hack.bin
	$(ARMCC)-size --format=berkeley --target=binary hack.bin

# Compiling rules are defined in ../Makefile
