-include ../config.mak

model?=xf1_101

# Bring C preprocessor macro into Make
include ../etc/util.mk
$(call importMacro, ../model/$(model).h, MEM_FREE_SPACE, %x)

# Target specific dependencies
HACK_BIN_DEPS=entry.o main.o lib.o stub.o fujihack.o
ALLOCER_BIN_DEPS=entry.o alloc.o stub.o

ARMCC?=arm-none-eabi
ARMCFLAGS?=-fpic -mcpu=cortex-a8 -include ../model/$(model).h -c
ARMLDFLAGS?=-Bstatic -T Linker.ld

RM=rm -rf

# Recompile when these are changed
EXTERN_DEPS=Makefile ../model/$(model).h *.h *.c

# The normal hack code
hack: hack.bin
	python3 ../ptp/load.py hack.bin

# Sets load address to allocated memory
allocer: allocer.bin
	python3 ../ptp/load.py allocer.bin

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

hack.bin: $(HACK_BIN_DEPS)
	$(ARMCC)-ld $(ARMLDFLAGS) $(HACK_BIN_DEPS) -o hack.elf
	$(ARMCC)-objcopy -O binary hack.elf hack.bin
	$(ARMCC)-size --format=berkeley --target=binary hack.bin

allocer.bin: $(ALLOCER_BIN_DEPS)
	$(ARMCC)-ld $(ARMLDFLAGS) $(ALLOCER_BIN_DEPS) -o allocer.elf
	$(ARMCC)-objcopy -O binary allocer.elf allocer.bin
	$(ARMCC)-size --format=berkeley --target=binary allocer.bin

clean:
	$(RM) *.elf *.o *.bin

.PHONY: clean hack
