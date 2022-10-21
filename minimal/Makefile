TOPL=../
include ../Makefile
-include ../config.mak

# Add in files from ../src
HACK_BIN_DEPS=$(addprefix ../src/,boot.o lib.o)
HACK_BIN_DEPS+=stub.o main.o

ARMCFLAGS?=-fpic -mcpu=cortex-a5 -include ../model/$(model).h -c -I ../src/
ARMLDFLAGS?=--gc-sections -Bstatic -T ../src/Linker.ld

# Recompile when these are changed
EXTERN_DEPS=Makefile ../model/$(model).h $(wildcard ../patch/*) $(wildcard *.h)

hack.bin: $(HACK_BIN_DEPS) $(EXTERN_DEPS)
	$(ARMCC)-ld $(ARMLDFLAGS) $(HACK_BIN_DEPS) -o hack.elf
	$(ARMCC)-objcopy -O binary hack.elf hack.bin
	$(ARMCC)-size --format=berkeley --target=binary hack.bin
