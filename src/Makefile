help:
	@echo "Targets: hack run hack.bin clean"

-include ../config.mak

model?=xf1_101

# Target specific dependencies
HACK_BIN_DEPS=boot.o main.o lib.o stub.o hijack.o screen.o posix.o

ARMCC?=arm-none-eabi
ARMCFLAGS?=-fpic -mcpu=cortex-a7 -include ../model/$(model).h -c
ARMLDFLAGS?=--gc-sections -Bstatic -T Linker.ld

# Remove unused sections
ARMCFLAGS+=-fdata-sections -ffunction-sections
ARMLDFLAGS+=--gc-sections

RM=rm -rf

# Recompile when these are changed
EXTERN_DEPS=Makefile ../model/$(model).h *.h

# The normal hack code
hack: hack.bin
	python3 ../ptp/load.py hack.bin

run:
	python3 ../ptp/run.py

# output rule for C files
%.o: %.c $(EXTERN_DEPS)
	$(ARMCC)-gcc $(ARMCFLAGS) $< -o $@

# output rule for assembly files
%.o: %.S $(EXTERN_DEPS)
	$(ARMCC)-gcc $(ARMCFLAGS) $< -o $@

# only stub.S is compiled with stubs
# Also, it depends on the model file
stub.o: stub.S ../model/$(model).h
	$(ARMCC)-gcc -D FPIC -D STUBS $(ARMCFLAGS) $< -o $@

hack.bin: $(HACK_BIN_DEPS) Linker.ld
	$(ARMCC)-ld $(ARMLDFLAGS) $(HACK_BIN_DEPS) -o hack.elf
	$(ARMCC)-objcopy -O binary hack.elf hack.bin
	$(ARMCC)-size --format=berkeley --target=binary hack.bin

font.bin: font/font.h
	$(ARMCC)-gcc -c font/font.c -o font.o
	$(ARMCC)-objcopy -O binary font.o font.bin

clean:
	$(RM) *.elf *.o *.bin

.PHONY: clean hack
