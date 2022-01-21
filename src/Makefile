MODEL?=xf1

# Bring C preprocessor macro into Make
include util.mk
$(call importMacro, ../model/$(MODEL).h, MEM_FREE_SPACE, %x)
ADDR=0x$(MEM_FREE_SPACE)

# These are set in order for the linker
FILES=entry.o test.o lib.o stub.o

CC=arm-none-eabi
CFLAG=-include ../model/$(MODEL).h -nostdlib -c
LDFLAGS=-Bstatic $(FILES) -Ttext $(ADDR)

RM=rm -rf

hack: main.o
	python3 ../ptp/load.py

# output rule for C files
%.o: %.c
	$(CC)-gcc $(CFLAG) $< -o $@

# output rule for assembly files
%.o: %.S
	$(CC)-gcc $(CFLAG) $< -o $@

# only stub.S is compiled with stubs
# Also, it depends on the model file
stub.o: stub.S ../model/$(MODEL).h
	$(CC)-gcc -D STUBS $(CFLAG) $< -o $@

main.o: $(FILES)
	$(CC)-ld $(LDFLAGS) -o main.elf
	$(CC)-objcopy -O binary main.elf main.o
	$(CC)-size --format=berkeley --target=binary main.o

clean:
	$(RM) *.elf *.o
