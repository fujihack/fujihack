TOPL=..
-include ../config.mak
include ../Makefile

# Add in files from ../src
HACK_BIN_DEPS=$(addprefix ../src/,boot.o lib.o)
HACK_BIN_DEPS+=stub.o main.o

# output rule for C files
%.o: %.c $(EXTERN_DEPS)
	$(ARMCC)-gcc $(ARMCFLAGS) $< -o $@

ARMCFLAGS=-fpic -mcpu=cortex-a5 -include ../model/$(model).h -c -I ../src/
ARMLDFLAGS=--gc-sections -Bstatic -T ../src/Linker.ld

hack.bin: $(HACK_BIN_DEPS) $(EXTERN_DEPS)
	$(ARMCC)-ld $(ARMLDFLAGS) $(HACK_BIN_DEPS) -o hack.elf
	$(ARMCC)-objcopy -O binary hack.elf hack.bin
	$(ARMCC)-size --format=berkeley --target=binary hack.bin
