model?=xf1

# Bring C preprocessor macro into Make
include util.mk
$(call importMacro, ../model/$(model).h, MEM_FREE_SPACE, %x)

# Target specific dependencies
HACK_BIN_DEPS=entry.o main.o lib.o stub.o
ALLOCER_BIN_DEPS=entry.o alloc.o stub.o

CC=arm-none-eabi
CFLAGS=-fpic -mcpu=cortex-a8 -include ../model/$(model).h -c
LDFLAGS=-Bstatic

RM=rm -rf

# Recompile when these are changed
EXTERN_DEPS=Makefile ../model/$(model).h

hack: hack.bin
	python3 ../ptp/load.py hack.bin

# Sets load address to allocated memory
allocer: allocer.bin
	python3 ../ptp/load.py allocer.bin

# output rule for C files
%.o: %.c $(EXTERN_DEPS)
	$(CC)-gcc $(CFLAGS) $< -o $@

# output rule for assembly files
%.o: %.S $(EXTERN_DEPS)
	$(CC)-gcc $(CFLAGS) $< -o $@

# only stub.S is compiled with stubs
# Also, it depends on the model file
stub.o: stub.S ../model/$(model).h
	$(CC)-gcc -D FPIC -D STUBS $(CFLAGS) $< -o $@

hack.bin: $(HACK_BIN_DEPS)
	$(CC)-ld $(LDFLAGS) $(HACK_BIN_DEPS) -o hack.elf
	$(CC)-objcopy -O binary hack.elf hack.bin
	$(CC)-size --format=berkeley --target=binary hack.bin

allocer.bin: $(ALLOCER_BIN_DEPS)
	$(CC)-ld $(LDFLAGS) $(ALLOCER_BIN_DEPS) -o allocer.elf
	$(CC)-objcopy -O binary allocer.elf allocer.bin
	$(CC)-size --format=berkeley --target=binary allocer.bin

clean:
	$(RM) *.elf *.o *.bin

.PHONY: clean hack
