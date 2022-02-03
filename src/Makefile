MODEL?=xf1

# Bring C preprocessor macro into Make
include util.mk
$(call importMacro, ../model/$(MODEL).h, MEM_FREE_SPACE, %x)

# Collect C files as .o
CFILES=$(subst .c,.o,$(wildcard *.c))

# lay out files in order for linker
FILES=entry.o $(CFILES) stub.o

CC=arm-none-eabi
CFLAGS=-mcpu=cortex-a8 -include ../model/$(MODEL).h -c
LDFLAGS=-Bstatic $(FILES) -Ttext 0x$(MEM_FREE_SPACE)

RM=rm -rf

hack: hack.bin
	python3 ../ptp/load.py

# output rule for C files
%.o: %.c
	$(CC)-gcc $(CFLAGS) $< -o $@

# output rule for assembly files
%.o: %.S
	$(CC)-gcc $(CFLAGS) $< -o $@

# only stub.S is compiled with stubs
# Also, it depends on the model file
stub.o: stub.S ../model/$(MODEL).h
	$(CC)-gcc -D STUBS $(CFLAGS) $< -o $@

hack.bin: $(FILES)
	$(CC)-ld $(LDFLAGS) -o hack.elf
	$(CC)-objcopy -O binary hack.elf hack.bin
	$(CC)-size --format=berkeley --target=binary hack.bin

clean:
	$(RM) *.elf *.o *.bin

.PHONY: clean hack
