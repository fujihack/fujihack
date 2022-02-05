model?=xf1

# Bring C preprocessor macro into Make
include util.mk
$(call importMacro, ../model/$(model).h, MEM_FREE_SPACE, %x)

# Collect C files as .o
CFILES=$(subst .c,.o,$(wildcard *.c))

# lay out files in order for linker
FILES=entry.o $(CFILES) stub.o

CC=arm-none-eabi
CFLAGS=-O2 -mcpu=cortex-a8 -include ../model/$(model).h -c
LDFLAGS=-Bstatic $(FILES) -Ttext 0x$(MEM_FREE_SPACE)

RM=rm -rf

# Recompile when these are changed
EXTERN_DEPS=Makefile ../model/$(model).h

hack: hack.bin
	python3 ../ptp/load.py

# output rule for C files
%.o: %.c $(EXTERN_DEPS)
	$(CC)-gcc $(CFLAGS) $< -o $@

# output rule for assembly files
%.o: %.S $(EXTERN_DEPS)
	$(CC)-gcc $(CFLAGS) $< -o $@

# only stub.S is compiled with stubs
# Also, it depends on the model file
stub.o: stub.S ../model/$(model).h
	$(CC)-gcc -D STUBS $(CFLAGS) $< -o $@

hack.bin: $(FILES)
	$(CC)-ld $(LDFLAGS) -o hack.elf
	$(CC)-objcopy -O binary hack.elf hack.bin
	$(CC)-size --format=berkeley --target=binary hack.bin

clean:
	$(RM) *.elf *.o *.bin

.PHONY: clean hack
